class Vertex {
    constructor(x, y) {
        this.x = x;
        this.y = y;
        this.dragging = false;
        this.radius = 10
    }

    render() {
        ellipse(this.x, this.y, this.radius);
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
    vertices = app.graph.map.map(p => new Vertex(p[0] * width, p[1] * height));
}

function draw() {
    background(250);
    fill(0);
    vertices.forEach(vertex => vertex.render());
}

function mousePressed() {
    vertices.forEach(vertex => {
        if (vertex.contains(mouseX, mouseY)) {
            vertex.startDrag();
        }
    });
}

function mouseReleased() {
    vertices.forEach(vertex => vertex.stopDrag());
}

function mouseDragged() {
    vertices.forEach(vertex => {
        if (vertex.dragging) {
            const newX = mouseX;
            const newY = mouseY;
            vertex.updatePosition(newX, newY);

            const index = vertices.indexOf(vertex);
            if (index !== -1) {
                app.graph.map[index] = [newX / width, newY / height];
            }
        }
    });
}
