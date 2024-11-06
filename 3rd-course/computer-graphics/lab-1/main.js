import { UI_ELEMENTS, showModal } from "./view.js";


let pointA = { x: UI_ELEMENTS.CIRCLE.x + 200, y: UI_ELEMENTS.CIRCLE.y - 200 };
let pointP = null; 
let step = 0;
const tangents = [];
let stopDrawing = false;
let tangentColor = '#1114d6';


function drawCircle() {
    UI_ELEMENTS.CTX.beginPath();
    UI_ELEMENTS.CTX.arc(UI_ELEMENTS.CIRCLE.x, UI_ELEMENTS.CIRCLE.y, UI_ELEMENTS.CIRCLE.radius, 0, Math.PI * 2);
    UI_ELEMENTS.CTX.stroke();
}

function drawPoint(point, color = 'red') {
    UI_ELEMENTS.CTX.fillStyle = color;
    UI_ELEMENTS.CTX.beginPath();
    UI_ELEMENTS.CTX.arc(point.x, point.y, 5, 0, Math.PI * 2);
    UI_ELEMENTS.CTX.fill();
}

function interpolatePoints(start, end, t) {
    return {
        x: start.x + (end.x - start.x) * t,
        y: start.y + (end.y - start.y) * t
    };
}

function drawTangents() {
    tangents.forEach((tangent) => {
        const { A, P, color } = tangent;
        
        UI_ELEMENTS.CTX.beginPath();
        UI_ELEMENTS.CTX.moveTo(A.x, A.y);
        UI_ELEMENTS.CTX.lineTo(P.x, P.y);
        UI_ELEMENTS.CTX.strokeStyle = color;
        UI_ELEMENTS.CTX.stroke();
    });
}

function animateTangent(A, P, color = tangentColor, duration = 1000, callback) {
    const startTime = performance.now();
    
    function drawFrame(currentTime) {
        const elapsed = currentTime - startTime;
        const t = Math.min(elapsed / duration, 1);

        UI_ELEMENTS.CTX.clearRect(0, 0, UI_ELEMENTS.CANVAS.width, UI_ELEMENTS.CANVAS.height);
        drawCircle();
        drawTangents();
        drawPoint(A, 'red');
        drawPoint(P, 'yellow');

        const currentPoint = interpolatePoints(A, P, t);

        UI_ELEMENTS.CTX.beginPath();
        UI_ELEMENTS.CTX.moveTo(A.x, A.y);
        UI_ELEMENTS.CTX.lineTo(currentPoint.x, currentPoint.y);
        UI_ELEMENTS.CTX.strokeStyle = color;
        UI_ELEMENTS.CTX.stroke();

        if (t < 1) {
            requestAnimationFrame(drawFrame);
        } else if (callback) {
            callback();
        }
    }

    requestAnimationFrame(drawFrame);
}

function getDist(x1, y1, x2, y2) {
    return Math.sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

function calculateTangent(A) {
    const dist = getDist(A.x, A.y, UI_ELEMENTS.CIRCLE.x, UI_ELEMENTS.CIRCLE.y);
    const radius = UI_ELEMENTS.CIRCLE.radius;

    if (dist <= radius) {
        throw new Error('Impossible to draw a tangent: point is incide the circle');
    }

    var pointDistance = {
        x: UI_ELEMENTS.CIRCLE.x - A.x,
        y: UI_ELEMENTS.CIRCLE.y - A.y,
        length: function () {
            return Math.sqrt(this.x * this.x + this.y * this.y)
        }
    }

    var alpha = Math.asin(radius / pointDistance.length());
    var beta = Math.atan2(pointDistance.y, pointDistance.x);
    var tangentAngle = beta - alpha;

    var L = {
        x: UI_ELEMENTS.CIRCLE.x + radius * Math.sin(tangentAngle),
        y: UI_ELEMENTS.CIRCLE.y + radius * -Math.cos(tangentAngle)
    };

    var P = {
        x: 2 * L.x - A.x,
        y: 2 * L.y - A.y
    };

    return { P, L };
}

function animateStep() {
    if (step === 0) {
        drawCircle();
        drawPoint(pointA, 'red');
        step++;
        setTimeout(animateStep, 500);
    } else {
        const result = calculateTangent(pointA);
        if (result && !stopDrawing) {
            pointP = result.P;

            animateTangent(pointA, pointP, tangentColor, 1000, () => {
                tangents.push({ A: pointA, P: pointP, color: tangentColor });

                pointA = pointP;
                step++;

                if (!stopDrawing) {
                    setTimeout(animateStep, 1000);
                }
            });
        }
    }
}

showModal();

function getRandomPointOutsideCircle() {
    let angle = Math.random() * Math.PI * 2;
    let dist = UI_ELEMENTS.CIRCLE.radius + 50 + Math.random() * 100;
    return {
        x: UI_ELEMENTS.CIRCLE.x + Math.cos(angle) * dist,
        y: UI_ELEMENTS.CIRCLE.y + Math.sin(angle) * dist
    };
}

UI_ELEMENTS.BTN_START.addEventListener('click', () => {
    UI_ELEMENTS.CIRCLE.radius = parseFloat(UI_ELEMENTS.RADIUS_INPUT.value);

    pointA = getRandomPointOutsideCircle();

    UI_ELEMENTS.MODAL.style.display = 'none';
    UI_ELEMENTS.BTN_STOP.style.display = 'block';
    setTimeout(animateStep, 1000);
});

UI_ELEMENTS.BTN_STOP.addEventListener('click', () => {
    stopDrawing = true;
    UI_ELEMENTS.BTN_STOP.style.display = 'none';
});