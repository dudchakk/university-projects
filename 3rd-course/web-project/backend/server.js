const express = require('express');
const multer = require('multer');
const cors = require('cors');
const { createServer } = require('http');
const { Server } = require('socket.io');
const { Worker } = require('worker_threads');
const path = require('path');

const app = express();
const httpServer = createServer(app);
const io = new Server(httpServer, {
    cors: {
        origin: 'http://localhost:3000',
        methods: ['GET', 'POST'],
        allowedHeaders: ['Content-Type'],
        credentials: true
    }
});

const PORT = process.env.PORT || 5000;

// Максимальна кількість невідомих у задачі (наприклад, 50)
const MAX_UNKNOWN_VARIABLES = 30000;
// Максимальний час виконання задачі (наприклад, 30 секунд)
const MAX_TIME_LIMIT = 30000; // 30 секунд

app.use(cors({
    origin: 'http://localhost:3000',
    methods: ['GET', 'POST'],
    allowedHeaders: ['Content-Type'],
}));

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

// Маршрут для обробки зображення
app.post('/api/recognize', upload.single('image'), (req, res) => {
    const imageBuffer = req.file.buffer;
    const jobId = Date.now().toString();

    // Перевірка максимальних обмежень
    if (req.file.size > 5 * 1024 * 1024) { // Приклад: обмеження за розміром файлу
        return res.status(400).json({ message: 'Файл занадто великий' });
    }

    // Перевірка кількості "невідомих" або складності задачі
    const taskComplexity = imageBuffer.length; // Це може бути параметр складності
    if (taskComplexity > MAX_UNKNOWN_VARIABLES) {
        return res.status(400).json({ message: `Задача занадто складна. Максимум: ${MAX_UNKNOWN_VARIABLES} змінних` });
    }

    res.status(200).json({ jobId, message: 'Завдання розпочато' });

    const worker = new Worker(path.join(__dirname, 'tesseractWorker.js'), {
        workerData: { imageBuffer }
    });

    tasks.set(jobId, worker);

    // Встановлюємо ліміт часу для скасування завдання
    const timeout = setTimeout(() => {
        worker.terminate(); // Завершуємо worker, якщо час виконання перевищено
        tasks.delete(jobId);
        io.to(jobId).emit('error', 'Час виконання задачі перевищив ліміт');
    }, MAX_TIME_LIMIT);

    worker.on('message', (message) => {
        if (message.type === 'progress') {
            io.to(jobId).emit('progress', message.data);
        } else if (message.type === 'result') {
            clearTimeout(timeout); // Якщо задача завершена в межах часу, скасовуємо таймер
            io.to(jobId).emit('result', message.data);
            tasks.delete(jobId);
            worker.terminate();
        } else if (message.type === 'error') {
            clearTimeout(timeout); // Якщо помилка, скасовуємо таймер
            io.to(jobId).emit('error', message.data);
            tasks.delete(jobId);
            worker.terminate();
        }
    });

    worker.on('error', (error) => {
        console.error('Помилка в worker:', error);
        clearTimeout(timeout); // Скасовуємо таймер при помилці
        // io.to(jobId).emit('error', 'Помилка обробки зображення');
        tasks.delete(jobId);
        worker.terminate();
    });

    worker.on('exit', (code) => {
        if (code !== 0) {
            console.error(`Worker завершився з кодом ${code}`);
            // io.to(jobId).emit('error', 'Помилка обробки зображення');
        }
        tasks.delete(jobId);
    });
});

// Маршрут для скасування завдання
app.post('/api/cancel/:jobId', (req, res) => {
    const jobId = req.params.jobId;
    const worker = tasks.get(jobId);

    if (worker) {
        worker.terminate(); // Завершуємо worker
        tasks.delete(jobId); // Видаляємо завдання з мапи
        res.status(200).json({ success: true, message: 'Задача скасована' });
    } else {
        res.status(404).json({ success: false, message: 'Задачу не знайдено' });
    }
});

// Запуск сервера
httpServer.listen(PORT, () => {
    console.log(`Server is running on http://localhost:${PORT}`);
});
