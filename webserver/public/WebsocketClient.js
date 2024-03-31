const ws = new WebSocket('wss://' + window.location.href.split("//")[1])
const command_history = []
let command_history_ptr = -1


ws.onmessage = function (event) {
    outputElem.textContent += event.data.endsWith("\n") ? event.data : event.data + "\n";
    outputElem.scrollTop = outputElem.scrollHeight;
    parser.parse(event.data);
};

ws.onerror = function (event) {
    console.error('WebSocket error:', event);
};

function sendData(data) {
    ws.send(data);
}

document.addEventListener('DOMContentLoaded', () => {
    document.getElementById("interface_form").addEventListener('submit', (e) => {
        e.preventDefault();
        const inputElement = document.getElementById('interface_flags');
        sendData(inputElement.value);

        if (inputElement.value && command_history.unshift(inputElement.value) > 10)
            command_history.pop()

        command_history_ptr = -1
        inputElement.value = '';
    });

    document.getElementById("interface_flags").addEventListener('keydown', (event) => {
        const field = document.getElementById("interface_flags")

        if (event.keyCode === 38) {
            event.preventDefault()
            command_history_ptr = Math.min(command_history.length - 1, ++command_history_ptr)
            field.value = command_history[command_history_ptr] || field.value
        } else if (event.keyCode === 40) {
            event.preventDefault()
            command_history_ptr = Math.max(0, --command_history_ptr)
            field.value = command_history[command_history_ptr] || field.value
        }

    });
});