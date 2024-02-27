const ws = new WebSocket('wss://' + window.location.href.split("//")[1]);
const outputElement = document.getElementById('output');

ws.onmessage = function(event) {
  outputElement.textContent += event.data + '\n';
  outputElement.scrollTop = outputElement.scrollHeight;
  const canvasContainer = document.getElementById('canvas');
canvasContainer.data.push(Math.round(Math.random() * 40))
};

ws.onerror = function(event) {
  console.error('WebSocket error:', event);
};
