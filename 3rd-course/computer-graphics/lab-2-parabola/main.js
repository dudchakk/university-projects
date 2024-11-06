function drawParabolaParametric(ctx, numPoints) {
  ctx.clearRect(0, 0, ctx.canvas.width, ctx.canvas.height);
  ctx.beginPath();

  const scale = 50;
  const offsetX = ctx.canvas.width / 2;
  const offsetY = ctx.canvas.height - 10;

  let tMin = -3;
  let tMax = 3;
  let step = (tMax - tMin) / (numPoints - 1);

  let errors = [];
  let norms = [];

  let t = tMin;
  let x = t;
  let y = t * t;

  let canvasX = offsetX + scale * x;
  let canvasY = offsetY - scale * y;

  ctx.moveTo(canvasX, canvasY);

  let approxY = y;

  for (let i = 1; i < numPoints; i++) {
    let prevT = t;
    t = tMin + step * i;

    let prevX = x;
    let prevY = y;

    x = t;
    y = t * t;

    canvasX = offsetX + scale * x;
    canvasY = offsetY - scale * y;

    approxY = prevY + (2 * prevT * step + step * step);

    let error = Math.abs(y - approxY);
    errors.push(error);

    ctx.lineTo(canvasX, canvasY);

    let curY = Math.abs(prevY - y) / 2
    let orgY = (prevX - x) * (prevX - x) / 4
    let curNorm = Math.abs(curY - orgY)
    norms.push(curNorm)
  }
  
  ctx.stroke();
  
  return { maxError: calculateErrorMetrics(errors), maxNorm: Math.max(...norms) };
}

function drawParabolaNonParametric(ctx, numPoints) {
  ctx.clearRect(0, 0, ctx.canvas.width, ctx.canvas.height);
  ctx.beginPath();
  const scale = 50;
  const offsetX = ctx.canvas.width / 2;
  const offsetY = ctx.canvas.height - 10;

  let xMin = -3;
  let xMax = 3;
  let step = (xMax - xMin) / (numPoints - 1);

  let errors = [];
  let norms = [];

  let x = xMin;
  let y = x * x; // y = x^2

  let canvasX = offsetX + scale * x;
  let canvasY = offsetY - scale * y;

  ctx.moveTo(canvasX, canvasY);

  for (let i = 1; i < numPoints; i++) {
    let prevX = x;
    let prevY = y;

    x = xMin + step * i;
    y = x * x; // y = x^2

    canvasX = offsetX + scale * x;
    canvasY = offsetY - scale * y;

    let approxY = prevY + (2 * prevX * step + step * step);
    let error = Math.abs(y - approxY);
    // console.log(error)
    errors.push(error);

    ctx.lineTo(canvasX, canvasY);

    let curY = Math.abs(prevY - y) / 2
    let orgY = (prevX - x) * (prevX - x) / 4
    let curNorm = Math.abs(curY - orgY)
    norms.push(curNorm)
  }
  ctx.stroke();

  return { maxError: calculateErrorMetrics(errors), maxNorm: Math.max(...norms) };
}

function calculateErrorMetrics(errors) {
  let maxError = Math.max(...errors);

  return maxError.toFixed(4);
}

function draw() {
  const parametricCanvas = document.getElementById('parametricCanvas');
  const nonParametricCanvas = document.getElementById('nonParametricCanvas');
  const parametricCtx = parametricCanvas.getContext('2d');
  const nonParametricCtx = nonParametricCanvas.getContext('2d');
  const numPoints = parseInt(document.getElementById('points').value);

  const startParametric = performance.now();
  let parametricResult = drawParabolaParametric(parametricCtx, numPoints);
  const endParametric = performance.now();
  document.getElementById('parametricTime').textContent = `${endParametric - startParametric} мс`;
  document.getElementById('parametricError').textContent = `${parametricResult.maxError}`;
  document.getElementById('parametricArea').textContent = `${parametricResult.maxNorm}`;

  const startNonParametric = performance.now();
  let nonParametricResult = drawParabolaNonParametric(nonParametricCtx, numPoints);
  const endNonParametric = performance.now();
  document.getElementById('nonParametricTime').textContent = `${endNonParametric - startNonParametric} мс`;
  document.getElementById('nonParametricError').textContent = `${nonParametricResult.maxError}`;
  document.getElementById('nonParametricArea').textContent = `${nonParametricResult.maxNorm}`;
}
