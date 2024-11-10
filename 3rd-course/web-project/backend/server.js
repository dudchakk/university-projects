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

app.use(cors({
    origin: 'http://localhost:3000',
    methods: ['GET', 'POST'],
    allowedHeaders: ['Content-Type'],
}));

const storage = multer.memoryStorage();
const upload = multer({ storage: storage });

// Об'єкт для зберігання активних worker'ів
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

    res.status(200).json({ jobId, message: 'Завдання розпочато' });

    // Створюємо новий worker для обробки зображення
    const worker = new Worker(path.join(__dirname, 'tesseractWorker.js'), {
        workerData: { imageBuffer }
    });

    // Зберігаємо worker у мапі
    tasks.set(jobId, worker);

    // Отримуємо повідомлення про прогрес
    worker.on('message', (message) => {
        if (message.type === 'progress') {
            io.to(jobId).emit('progress', message.data);
        } else if (message.type === 'result') {
            io.to(jobId).emit('result', message.data);
            tasks.delete(jobId); // Видаляємо завдання після завершення
            worker.terminate(); // Завершуємо worker
        } else if (message.type === 'error') {
            io.to(jobId).emit('error', message.data);
            tasks.delete(jobId); // Видаляємо завдання після помилки
            worker.terminate(); // Завершуємо worker
        }
    });

    worker.on('error', (error) => {
        console.error('Помилка в worker:', error);
        io.to(jobId).emit('error', error);
        tasks.delete(jobId); // Видаляємо завдання у разі помилки
        worker.terminate(); // Завершуємо worker
    });

    worker.on('exit', (code) => {
        if (code !== 0) {
            console.error(`Worker завершився з кодом ${code}`);
            // io.to(jobId).emit('error', 'Помилка обробки зображення');
        }
        tasks.delete(jobId); // Видаляємо завдання після завершення
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
