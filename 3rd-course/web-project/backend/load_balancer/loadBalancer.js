const http = require("http");
const { createProxyServer } = require("http-proxy");

// Створюємо проксі-сервер з підтримкою WebSocket
const proxy = createProxyServer({ ws: true });

// Масив серверів для балансування навантаження
const servers = ["http://localhost:3001", "http://localhost:3002"];
const activeRequests = Array(servers.length).fill(0);

// Створюємо HTTP сервер, який буде балансувати навантаження
const server = http.createServer((req, res) => {
  // Налаштування CORS для HTTP-запитів
  const allowedOrigins = ["http://localhost:5173", "http://localhost:3000"]; // Додаємо обидва джерела
  const origin = req.headers.origin;

  if (allowedOrigins.includes(origin)) {
    res.setHeader("Access-Control-Allow-Origin", origin); // Дозволяємо запити тільки з цих джерел
    res.setHeader("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
    res.setHeader("Access-Control-Allow-Headers", "Content-Type, Authorization");
  }

  // Вибір серверу з мінімальним навантаженням
  const leastLoadedServerIndex = activeRequests.indexOf(Math.min(...activeRequests));
  activeRequests[leastLoadedServerIndex]++;

  // Перенаправляємо запит до обраного сервера
  proxy.web(req, res, { target: servers[leastLoadedServerIndex] });
  console.log(`Forwarding request to server: ${servers[leastLoadedServerIndex]}`);

  // Зменшуємо лічильник активних запитів після завершення обробки
  res.on("finish", () => {
    activeRequests[leastLoadedServerIndex]--;
  });
});

// Налаштовуємо проксі для WebSocket з'єднань
server.on("upgrade", (req, socket, head) => {
  const leastLoadedServerIndex = activeRequests.indexOf(Math.min(...activeRequests));
  activeRequests[leastLoadedServerIndex]++;

  // Перенаправляємо WebSocket з'єднання
  proxy.ws(req, socket, head, { target: servers[leastLoadedServerIndex] });
  console.log(`Upgrading WebSocket connection to server: ${servers[leastLoadedServerIndex]}`);

  // Зменшуємо лічильник активних запитів після завершення обробки
  socket.on("close", () => {
    activeRequests[leastLoadedServerIndex]--;
  });
});

server.listen(3015, () => {
  console.log("Load Balancer running on port 3015");
});