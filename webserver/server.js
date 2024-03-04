const express = require('express');
const { WebSocketServer } = require('ws');
const { spawn } = require('child_process');
const https = require('https');
const fs = require('fs');
const app = express();
const PORT = process.env.PORT || 8443
const MYAPP_FLAGS = process.env.MYAPP_FLAGS || "--test"

// Load SSL/TLS certificates
const server = https.createServer({
  cert: fs.readFileSync('certificates/cert.pem'),
  key: fs.readFileSync('certificates/key.pem')
}, app);

// Serve static files from the 'public' directory
app.use(express.static('public'));

// Listen on HTTPS
server.listen(PORT, () => {
  console.log(`Secure server running at https://localhost:${PORT}`);
});

// Set up secure WebSocket server
const wss = new WebSocketServer({ server });

wss.on('connection', (ws) => {
  console.log('Client connected');

  // Spawn the child process
  // const child = spawn('./public/myapp.exe', [...MYAPP_FLAGS.split(" ")]);
  const child = spawn('./public/myapp.exe', ["-m", "10"]);

  // Stream the output of the child process to the WebSocket
  child.stdout.on('data', (data) => {
    ws.send(data.toString());
  });

  child.stderr.on('data', (data) => {
    ws.send(data.toString());
  });

  child.on('close', (code) => {
    ws.send(`Child process exited with code ${code}`);
  });

  // Handle WebSocket messages from the client (if necessary)
  ws.on('message', (message) => {
    console.log('Received:', message.toString());

    // Spawn the child process
    const child = spawn('./public/myapp.exe', [...message.toString().split(" ")]);

    // Stream the output of the child process to the WebSocket
    child.stdout.on('data', (data) => {
      ws.send(data.toString());
    });

    child.stderr.on('data', (data) => {
      ws.send(data.toString());
    });

    child.on('close', (code) => {
      ws.send(`Child process exited with code ${code}`);
    });

  });

  // Handle client disconnect
  ws.on('close', () => {
    console.log('Client disconnected');
    // child.kill(); // Ensure the child process is killed if the client disconnects
  });
});
