const express = require('express');
const multer = require('multer');
const cors = require('cors');
const { createServer } = require('http');
const { Server } = require('socket.io');
const { Worker } = require('worker_threads');
const path = require('path');
const mongoose = require('mongoose');
const Task = require('./models/task');
require('dotenv').config();

const app = express();
const httpServer = createServer(app);
const io = new Server(httpServer, {
    cors: {
        origin: 'http://localhost:3000',
        methods: ['GET', 'POST','DELETE'],
        allowedHeaders: ['Content-Type'],
        credentials: true
    }
});

const PORT = process.env.PORT || 5000;
mongoose.connect(process.env.MONGO_URI)
.then(() => console.log('Connected to MongoDB'))
.catch(err => console.log('MongoDB connection error:', err));

// Максимальна кількість невідомих у задачі (наприклад, 50)
const MAX_UNKNOWN_VARIABLES = 30000;
// Максимальний час виконання задачі (наприклад, 30 секунд)
const MAX_TIME_LIMIT = 30000; // 30 секунд

app.use(cors());

const storage = multer.memoryStorage();
const upload = multer({ storage: storage });

const tasks = new Map();

io.on('connection', (socket) => {
    console.log('Новий клієнт підключено:', socket.id);

    socket.on('join', (jobId) => {
        socket.join(jobId);
        console.log(`Клієнт ${socket.id} приєднався до кімнати ${jobId}`);
    });

    socket.on('disconnect', () => {
        console.log('Клієнт відключився:', socket.id);
    });
});
app.delete('/api/clear-tasks', async (req, res) => {
    try {
        // Видалення всіх задач з бази даних
        const deletedTasks = await Task.deleteMany({});
        res.status(200).json({
            message: `Видалено ${deletedTasks.deletedCount} задач`,
        });
    } catch (error) {
        console.error('Помилка очищення задач:', error);
        res.status(500).json({ message: 'Не вдалося очистити задачі.' });
    }
});
// Маршрут для обробки зображення
app.post('/api/recognize', upload.single('image'), async (req, res) => {
    const imageBuffer = req.file.buffer;
    const jobId = Date.now().toString();
    const inProgressCount = await Task.countDocuments({ status: 'in_progress' });

    if (inProgressCount >= 5) {
        io.emit('error', 'Не можна створити більше 5 задач підряд');
        return res.status(400).json({ message: 'Не можна створити більше 5 задач підряд' });
    }
    const task = new Task({
        jobId,
        fileName: req.file.originalname,
        status: 'in_progress',
        progress: 0,
    });
    io.emit('update-history', task); 


    await task.save();
    Task.deleteMany({})

    // Перевірка максимальних обмежень
    if (req.file.size > 5 * 1024 * 1024) { // Приклад: обмеження за розміром файлу
        return res.status(400).json({ message: 'Файл занадто великий' });
    }

    // Перевірка кількості "невідомих" або складності задачі
    const taskComplexity = imageBuffer.length; // Це може бути параметр складності
    if (taskComplexity > MAX_UNKNOWN_VARIABLES) {
        const task = await Task.findOneAndUpdate({ jobId }, { status: 'failed' });
        io.emit('update-history');  
        return res.status(400).json({ message: `Задача занадто складна. Максимум: ${MAX_UNKNOWN_VARIABLES} змінних` });
    }

    res.status(200).json({ jobId, message: 'Завдання розпочато' });

    const worker = new Worker(path.join(__dirname, 'tesseractWorker.js'), {
        workerData: { imageBuffer }
    });

    tasks.set(jobId, worker);
    io.emit('update-history'); 


    // Встановлюємо ліміт часу для скасування завдання
    const timeout = setTimeout(async() => {
        worker.terminate(); // Завершуємо worker, якщо час виконання перевищено
        tasks.delete(jobId);
        io.to(jobId).emit('error', 'Час виконання задачі перевищив ліміт');
        const task = await Task.findOneAndUpdate({ jobId }, { status: 'failed' });
        io.emit('update-history');  
    }, MAX_TIME_LIMIT);

    worker.on('message', async (message) => {
        if (message.type === 'progress') {
            io.to(jobId).emit('progress', message.data);
        } else if (message.type === 'result') {
            clearTimeout(timeout);
            const task = await Task.findOneAndUpdate({ jobId }, { status: 'completed', resultText: message.data });
            io.to(jobId).emit('result', message.data);
            io.emit('update-history');  
            tasks.delete(jobId);
            worker.terminate();
        } else if (message.type === 'error') {
            clearTimeout(timeout);
            io.to(jobId).emit('error', message.data);
            tasks.delete(jobId);
            worker.terminate();
        }
    });

    worker.on('error', (error) => {
        console.error('Помилка в worker:', error);
        clearTimeout(timeout); 
        tasks.delete(jobId);
        worker.terminate();
    });

    worker.on('exit', (code) => {
        if (code !== 0) {
            console.error(`Worker завершився з кодом ${code}`);
        }
        tasks.delete(jobId);
    });
});

// Маршрут для скасування завдання
app.post('/api/cancel/:jobId', async(req, res) => {
    const jobId = req.params.jobId;
    const worker = tasks.get(jobId);

    if (worker) {
        worker.terminate(); // Завершуємо worker
        tasks.delete(jobId); // Видаляємо завдання з мапи
        const task = await Task.findOneAndUpdate({ jobId }, { status: 'canceled' });
        io.emit('update-history', task);  // Оновлення історії
        res.status(200).json({ success: true, message: 'Задача скасована' });
    } else {
        res.status(404).json({ success: false, message: 'Задачу не знайдено' });
    }
});

// Маршрут для отримання історії
app.get('/api/history', async (req, res) => {
    try {
        const tasksHistory = await Task.find().sort({ createdAt: -1 }).limit(10); // Останні 10 задач
        res.json(tasksHistory);
    } catch (err) {
        res.status(500).json({ message: 'Помилка при отриманні історії', error: err });
    }
});

// Запуск сервера
httpServer.listen(PORT, () => {
    console.log(`Server is running on http://localhost:${PORT}`);
});
