const express = require('express');
const multer = require('multer');
const cors = require('cors');
const { createServer } = require('http');
const { Server } = require('socket.io');
const Tesseract = require('tesseract.js');

const app = express();
const httpServer = createServer(app);
const io = new Server(httpServer, {
    cors: {
        origin: 'http://localhost:3000', // Дозволений домен для фронтенду
        methods: ['GET', 'POST'],
        allowedHeaders: ['Content-Type'],
        credentials: true
    }
});

const PORT = process.env.PORT || 5000;

// Налаштування CORS для Express
app.use(cors({
    origin: 'http://localhost:3000',
    methods: ['GET', 'POST'],
    allowedHeaders: ['Content-Type'],
}));

const storage = multer.memoryStorage();
const upload = multer({ storage: storage });

// Підключення клієнтів до кімнати за jobId
io.on('connection', (socket) => {
    console.log('Новий клієнт підключено:', socket.id);

    // Підписка клієнта на конкретне завдання
    socket.on('join', (jobId) => {
        socket.join(jobId);
        console.log(`Клієнт ${socket.id} приєднався до кімнати ${jobId}`);
    });

    // Від'єднання клієнта
    socket.on('disconnect', () => {
        console.log('Клієнт відключився:', socket.id);
    });
});

// Маршрут для обробки зображення
app.post('/api/recognize', upload.single('image'), (req, res) => {
    const imageBuffer = req.file.buffer;
    const jobId = Date.now().toString(); // Унікальний ідентифікатор задачі як рядок

    // Відправляємо jobId клієнту для підключення до кімнати
    res.status(200).json({ jobId, message: 'Завдання розпочато' });

    // Виконання обробки зображення через Tesseract.js
    Tesseract.recognize(
        imageBuffer,
        'eng',
        {
            logger: info => {
                io.to(jobId).emit('progress', info); // Надсилаємо подію прогресу
            }
        }
    ).then(({ data: { text } }) => {
        io.to(jobId).emit('result', text); // Відправляємо результат після завершення
    }).catch(error => {
        console.error(error);
        io.to(jobId).emit('error', 'Помилка обробки зображення'); // Відправляємо помилку у кімнату
    });
});

// Запуск сервера
httpServer.listen(PORT, () => {
    console.log(`Server is running on http://localhost:${PORT}`);
});
