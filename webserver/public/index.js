const outputElem = document.getElementById('output')
const canvasElem = document.getElementById('canvas')

let app = {
    graph: {
        map: []
    }
}

function printCoordinates() {
    let command = `-g ${app.graph.map.length}`
    app.graph.map.forEach(p => {
        command += `_${p[0]}_${p[1]}`
    });
    console.log(command)
    return command
}

document.addEventListener('DOMContentLoaded', () => {
    document.getElementById("interface_validate").addEventListener('click', (e) => {
        sendData(printCoordinates());
    });
});