const WebSocket = require('ws');
const net = require('net');

const WS_PORT = process.env.WS_PORT || 8080;
const HW_HOST = process.env.HW_HOST || 'localhost';
const HW_PORT = process.env.HW_PORT || 46631;

const wss = new WebSocket.Server({ port: WS_PORT });

console.log(`WebWars Gateway listening on ws://localhost:${WS_PORT}`);
console.log(`Forwarding to Hedgewars server at ${HW_HOST}:${HW_PORT}`);

wss.on('connection', (ws, req) => {
  const clientIp = req.socket.remoteAddress;
  console.log(`[${clientIp}] Client connected`);

  // Connect to Hedgewars server
  const tcpClient = net.connect(HW_PORT, HW_HOST, () => {
    console.log(`[${clientIp}] Connected to Hedgewars server`);
  });

  // WebSocket → TCP
  ws.on('message', (data) => {
    try {
      tcpClient.write(data);
    } catch (err) {
      console.error(`[${clientIp}] Error writing to TCP:`, err.message);
      ws.close();
    }
  });

  // TCP → WebSocket
  tcpClient.on('data', (data) => {
    try {
      if (ws.readyState === WebSocket.OPEN) {
        ws.send(data);
      }
    } catch (err) {
      console.error(`[${clientIp}] Error sending to WebSocket:`, err.message);
      tcpClient.end();
    }
  });

  // Handle disconnections
  ws.on('close', () => {
    console.log(`[${clientIp}] WebSocket closed`);
    tcpClient.end();
  });

  tcpClient.on('close', () => {
    console.log(`[${clientIp}] TCP connection closed`);
    ws.close();
  });

  // Handle errors
  ws.on('error', (err) => {
    console.error(`[${clientIp}] WebSocket error:`, err.message);
    tcpClient.end();
  });

  tcpClient.on('error', (err) => {
    console.error(`[${clientIp}] TCP error:`, err.message);
    ws.close();
  });
});

wss.on('error', (err) => {
  console.error('WebSocket server error:', err);
});

process.on('SIGINT', () => {
  console.log('\nShutting down gateway...');
  wss.close(() => {
    console.log('Gateway closed');
    process.exit(0);
  });
});
