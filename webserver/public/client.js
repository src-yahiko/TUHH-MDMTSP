const ws = new WebSocket('wss://' + window.location.href.split("//")[1]);
const outputElement = document.getElementById('output');

ws.onmessage = function(event) {
  outputElement.textContent += event.data + '\n';
  outputElement.scrollTop = outputElement.scrollHeight;

  if (String(event.data).startsWith("#MAP")) {
    const maparr = event.data.split("#")[2].split(" ")
    let maplen = parseInt(maparr[0])

    let mymap = []

    for (let i = 1; i <= maplen; ++i) {
      const x = maparr[(i * 2) - 1]
      const y = maparr[i * 2]
      mymap.push([x, y])
    }
    canvasContainer.MAP = mymap
    console.log(canvasContainer.MAP)
  }

};

ws.onerror = function(event) {
  console.error('WebSocket error:', event);
};

// Function to send data through the WebSocket
function sendData(data) {
  ws.send(data);
}

// Prevent the default form submission and use sendData instead
document.addEventListener('DOMContentLoaded', () => {
  const form = document.querySelector('form');
  form.addEventListener('submit', (e) => {
    e.preventDefault(); // Prevent the actual form submission
    const inputElement = document.getElementById('interface_flags');
    sendData(inputElement.value); // Send the input's value through the WebSocket
    inputElement.value = ''; // Optionally clear the input after sending
  });
});