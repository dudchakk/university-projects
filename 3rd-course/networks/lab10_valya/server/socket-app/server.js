const express = require('express');
const http = require('http');
const { Server } = require('socket.io');
const cors = require('cors');

const app = express();
const server = http.createServer(app);
const io = new Server(server, {
    cors: {
        origin: '*',
        methods: ['GET', 'POST'] 
    }
});

const mode = process.argv[2] || 'sequential'; // parallel or sequential
console.log(`Server running in ${mode} mode`);

app.use(cors({
    origin: '*', 
    methods: ['GET', 'POST'], 
    allowedHeaders: ['Content-Type', 'Authorization'] 
}));


io.on('connection', (socket) => {
    console.log('A user connected');

    socket.on('login', ({ login, password }) => {
        console.log(`Received login: ${login}, password: ${password}`);

        const response = {
            success: true,
            message: `Вітаю, ${login}!` 
        };

        if (mode === 'sequential') {
            setTimeout(() => {
                io.emit('greeting', response);
            }, 2000);
        } else {

            io.emit('greeting', response);
        }
    });

    socket.on('disconnect', () => {
        console.log('A user disconnected');
    });
});

const PORT = 3001;
server.listen(PORT, () => {
    console.log(`Server is listening on http://localhost:${PORT}`);
});
