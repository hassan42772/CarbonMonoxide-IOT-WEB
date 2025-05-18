const express = require('express');
const http = require('http');
const { Server } = require('socket.io');
const { SerialPort } = require('serialport');
const { ReadlineParser } = require('@serialport/parser-readline');

const portName = 'COM4'; // Change to your actual COM port

const app = express();
const server = http.createServer(app);
const io = new Server(server);

app.use(express.static('public'));

server.listen(3001, () => {
  console.log('Server running at http://localhost:3001');
});

const port = new SerialPort({ path: portName, baudRate: 9600 });
const parser = port.pipe(new ReadlineParser({ delimiter: '\n' }));

parser.on('data', (data) => {
  // console.log('Serial:', data);
  const match = data.match(/Gas Level:\s*(\d+)/);
  if (match) {
    const gasValue = parseInt(match[1]);
    io.emit('gasData', gasValue);
  }
});
