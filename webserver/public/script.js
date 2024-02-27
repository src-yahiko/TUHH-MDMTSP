
const canvasContainer = document.getElementById('canvas');
const PADDING = 15;
function setup() {
  const w = canvasContainer.offsetWidth;
  const h = canvasContainer.offsetHeight;
  const canvas = createCanvas(w, h);
  canvas.parent('canvas'); 
}

function windowResized() {
  const w = canvasContainer.offsetWidth;
  const h = canvasContainer.offsetHeight;
  resizeCanvas(w, h);
}


function draw() {
  background(250);
  fill(0)

  if (canvasContainer.MAP != null && canvasContainer.MAP.length > 0) {
    canvasContainer.MAP.forEach(point => {
      ellipse(point[0] * (width - 2 * PADDING) + PADDING, point[1] * (height - 2 * PADDING) + PADDING, 13);
    });
  }
}
