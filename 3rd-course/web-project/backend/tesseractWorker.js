const { parentPort, workerData } = require('worker_threads')
const Tesseract = require('tesseract.js')

Tesseract.recognize(workerData.imageBuffer, 'eng', {
  logger: (info) => parentPort.postMessage({ type: 'progress', data: info }),
})
  .then(({ data: { text } }) => {
    parentPort.postMessage({ type: 'result', data: text })
  })
  .catch((error) => {
    parentPort.postMessage({
      type: 'error',
      data: 'Помилка обробки зображення',
    })
  })
