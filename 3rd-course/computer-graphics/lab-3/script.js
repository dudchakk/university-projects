const canvas = document.getElementById('canvas');
canvas.width = 320;
canvas.height = 320;
const ctx = canvas.getContext('2d');

const gridSize = 32;
const pixelSize = 10;
const pseudoBuffer = new Array(gridSize * gridSize).fill(0);

function setPixel(x, y, value = 1) {
    if (x >= 0 && x < gridSize && y >= 0 && y < gridSize) {
        pseudoBuffer[y * gridSize + x] = value;
        ctx.fillRect(x * pixelSize, y * pixelSize, pixelSize, pixelSize);
    }
}

function drawLineBresenhamAlgorithm(x1, y1, x2, y2) {
    let dx = Math.abs(x2 - x1);
    let dy = Math.abs(y2 - y1);
    let sx = x1 < x2 ? 1 : -1;
    let sy = y1 < y2 ? 1 : -1;
    let err = dx - dy;

    const pixels = [];

    while (true) {
        setPixel(x1, y1);
        pixels.push({ x: x1, y: y1 });

        if (x1 === x2 && y1 === y2) break;

        const e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }

    return pixels;
}

function clearCanvas() {
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    ctx.strokeStyle = 'black';
    ctx.lineWidth = 1;
    for (let i = 0; i <= gridSize; i++) {
        ctx.beginPath();
        ctx.moveTo(i * pixelSize, 0);
        ctx.lineTo(i * pixelSize, canvas.height);
        ctx.moveTo(0, i * pixelSize);
        ctx.lineTo(canvas.width, i * pixelSize);
        ctx.stroke();
    }
}

const circleCenter = { x: Math.floor(gridSize / 2), y: Math.floor(gridSize / 2) };
const radius = Math.floor(gridSize / 2);

function drawCircleLines() {
    const pixelListDiv = document.getElementById('pixel-list');
    pixelListDiv.innerHTML = '';

    const linesCount = 16;
    const angleStep = (2 * Math.PI) / linesCount;

    for (let i = 0; i < linesCount; i++) {
        const angle = i * angleStep;
        const x2 = Math.round(circleCenter.x + radius * Math.cos(angle));
        const y2 = Math.round(circleCenter.y + radius * Math.sin(angle));

        const pixels = drawLineBresenhamAlgorithm(circleCenter.x, circleCenter.y, x2, y2);
        const pixelStr = `Лінія ${i + 1}: ` + pixels.map(p => `(${p.x}, ${p.y})`).join(', ');
        const lineElement = document.createElement('div');
        lineElement.textContent = pixelStr;
        pixelListDiv.appendChild(lineElement);
    }
}

function main() {
    clearCanvas();
    ctx.fillStyle = 'blue';
    setPixel(circleCenter.x, circleCenter.y);

    ctx.fillStyle = 'red';
    drawCircleLines();
}

document.getElementById('draw-lines').addEventListener('click', main);

clearCanvas();
