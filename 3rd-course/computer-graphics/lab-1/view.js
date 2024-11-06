export const UI_ELEMENTS = {
    CANVAS: document.getElementById('myCanvas'),
    CTX: document.getElementById('myCanvas').getContext('2d'),
    CIRCLE: {
        x: document.getElementById('myCanvas').width / 2,
        y: document.getElementById('myCanvas').height / 2,
        radius: 100
    },
    MODAL: document.getElementById('radiusModal'),
    RADIUS_INPUT: document.getElementById('radiusInput'),
    BTN_START: document.getElementById('startAnimation'),
    BTN_STOP: document.getElementById('stopAnimation'),
};

export function showModal() {
    UI_ELEMENTS.MODAL.style.display = 'block';
}