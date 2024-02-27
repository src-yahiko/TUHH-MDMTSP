
const canvasContainer = document.getElementById('canvas');
canvasContainer.data = [4,2,6,4,5]

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
  const data = canvasContainer.data
  const step = (width - 40) / data.length
  const maxVal = Math.max(...data)
  const normal = data.map(val => val / maxVal)
  const y_base = height - (height / 4)
  line(20, y_base, width - 20, y_base)


  for (let i = 1; i < data.length; ++i) {
    const current_x = step * i + 20
    const current_y = y_base - normal[i] * height / 2
    const last_x = step * (i-1) + 20
    const last_y = y_base - normal[i-1] * height / 2
    line(last_x, last_y, current_x, current_y )
  }
  
}
