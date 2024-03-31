const outputElem = document.getElementById('output')
const canvasElem = document.getElementById('canvas')

let app = {
    graph: {
        map: [],
        edges: []
    },
    mst: false
}

function printCoordinates() {
    let command = `-i ${app.graph.map.length}`
    app.graph.map.forEach(p => {
        command += `_${p[0]}_${p[1]}`
    });
    return command
}


// document.addEventListener('DOMContentLoaded', () => {
//     document.getElementById("interface_validate").addEventListener('click', (e) => {
//         sendData(printCoordinates());
//     });
// });


// const toggleMST = () => {
//     app.mst = !app.mst
//     if (app.mst == true)
//      {
//         document.getElementById("interface_toggleMST").style.backgroundColor = "green";
//      } else {
//          document.getElementById("interface_toggleMST").style.backgroundColor = "black";
//         }
// }

// const MST = () => {
//     sendData(printCoordinates())
// }

// const interval = setInterval(() => { if (app.mst == true) { sendData(printCoordinates()) } }, 400)