const outputElem = document.getElementById('output')
const canvasElem = document.getElementById('canvas')

let app = {
    graph: {
        map: [],
        edges: []
    },
    mst: false
}

function getGraphString() {
    // let command = `-i ${app.graph.map.length}`
    // app.graph.map.forEach(p => {
    // command += `_${p[0]}_${p[1]}`
    // });
    let points = "";
    let depots = "";

    const m = Object.entries(app.graph.map)
    m.forEach((p,) => {
        let idx = p[0]
        let point = p[1]
        if (point[2])
            depots += `#DEPOT#${idx}\n`

        points += `#POINT#${idx}_${point[0]}_${point[1]}\n`
    })

    return `${points}${depots}`;
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

const MST = () => {
    // sendData(printCoordinates())
    sendCommand("MST", getGraphString())
}


const CSF = () => {
    // sendData(printCoordinates())
    sendCommand("CSF", getGraphString())
}

const DRPP = () => {
    sendCommand("DRPP", getGraphString())
}


// const interval = setInterval(() => { if (app.mst == true) { sendData(printCoordinates()) } }, 400)