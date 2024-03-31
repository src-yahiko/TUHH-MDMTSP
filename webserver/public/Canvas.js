class Vertex {
    constructor(x, y, depot) {
        this.x = x;
        this.y = y;
        this.dragging = false;
        this.radius = 10
        this.isDepot = depot || false
    }

    render() {
        strokeWeight(0)
        if (this.isDepot) {
            fill(0, 0, 255)
            rectMode(RADIUS)
            rect(this.x, this.y, this.radius / 2)
        }
        else {
            fill(0, 0, 0)
            ellipse(this.x, this.y, this.radius);
        }
    }

    contains(px, py) {
        const d = dist(px, py, this.x, this.y);
        return d < this.radius;
    }

    startDrag() {
        this.dragging = true;
    }

    stopDrag() {
        this.dragging = false;
    }

    updatePosition(newX, newY) {
        if (this.dragging) {
            this.x = newX;
            this.y = newY;
        }
    }
}

let vertices = [];

function setup() {
    const canvas = document.getElementById('canvas');
    const w = canvas.offsetWidth;
    const h = canvas.offsetHeight;
    const p5canvas = createCanvas(w, h);
    p5canvas.parent('canvas');
    // vertices = Object.values(app.graph.map).map(p => new Vertex(p[0] * width, p[1] * height, p[2]));
    vertices = {}
    for (const [nodeId, p] of Object.entries(app.graph.map)) {
        vertices[nodeId] = new Vertex(p[0] * width, p[1] * height, p[2])
    }
}

function draw() {
    // background();
    fill(0);
    app.graph.edges.forEach(e => {
        const v_from = vertices[e[0]]
        const v_to = vertices[e[1]]
        const idx_col = 2.8 * e[2];
        stroke(110)
        strokeWeight(idx_col)
        line(v_from.x, v_from.y, v_to.x, v_to.y)
    })
    Object.values(vertices).map(vertex => vertex.render());
}

// function mousePressed() {
//     Object.values(vertices).map(vertex => {
//         if (vertex.contains(mouseX, mouseY)) {
//             vertex.startDrag();
//         }
//     });
// }

// function mouseReleased() {
//     Object.values(vertices).map(vertex => {
//         vertex.stopDrag()
//     })
// }

// function mouseDragged() {

//     Object.values(vertices).map(vertex => {

//         if (vertex.dragging) {
//             const newX = mouseX;
//             const newY = mouseY;
//             vertex.updatePosition(newX, newY);

//             const index = vertices.indexOf(vertex);
//             if (index !== -1) {
//                 app.graph.map[index] = [newX / width, newY / height];
//             }
//         }
//     });
// }
