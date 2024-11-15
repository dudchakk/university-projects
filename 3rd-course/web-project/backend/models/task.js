const mongoose = require('mongoose')

const taskSchema = new mongoose.Schema({
  jobId: {
    type: String,
    required: true,
    unique: true,
  },
  fileName: String,
  resultText: String,
  createdAt: {
    type: Date,
    default: Date.now,
  },
  status: {
    type: String,
    enum: ['in_progress', 'completed', 'failed', 'canceled'],
    default: 'in_progress',
  },
  progress: Number,
})

const Task = mongoose.model('Task', taskSchema)
module.exports = Task
