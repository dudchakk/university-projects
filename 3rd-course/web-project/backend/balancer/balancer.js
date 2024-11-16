const http = require('http')
const { createProxyServer } = require('http-proxy')

const proxy = createProxyServer({ ws: true })

const servers = ['http://localhost:3001', 'http://localhost:3002']
const activeRequests = Array(servers.length).fill(0)

const server = http.createServer((req, res) => {
  const allowedOrigins = ['http://localhost:3000']
  const origin = req.headers.origin

  if (allowedOrigins.includes(origin)) {
    res.setHeader('Access-Control-Allow-Origin', origin)
    res.setHeader(
      'Access-Control-Allow-Methods',
      'GET, POST, PUT, DELETE, OPTIONS'
    )
    res.setHeader('Access-Control-Allow-Headers', 'Content-Type, Authorization')
  }

  const leastLoadedServerIndex = activeRequests.indexOf(
    Math.min(...activeRequests)
  )
  activeRequests[leastLoadedServerIndex]++

  proxy.web(req, res, { target: servers[leastLoadedServerIndex] })
  console.log(
    `Forwarding request to server: ${servers[leastLoadedServerIndex]}`
  )

  res.on('finish', () => {
    activeRequests[leastLoadedServerIndex]--
  })
})

server.listen(3015, () => {
  console.log('Load Balancer running on port 3015')
})
