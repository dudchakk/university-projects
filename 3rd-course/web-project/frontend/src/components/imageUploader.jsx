import React, { useState, useEffect } from 'react'
import {
  Box,
  Button,
  CircularProgress,
  Typography,
  Alert,
  TextField,
  List,
  ListItem,
  ListItemText,
} from '@mui/material'
import { CloudUpload as CloudUploadIcon } from '@mui/icons-material'
import io from 'socket.io-client'

const socket = io('http://localhost:5002')

function TextRecognition() {
  const [progress, setProgress] = useState(null)
  const [result, setResult] = useState('')
  const [error, setError] = useState('')
  const [jobId, setJobId] = useState(null)
  const [history, setHistory] = useState([])

  const fetchHistory = async () => {
    try {
      const response = await fetch('http://localhost:5002/api/history')
      const data = await response.json()
      setHistory(data)
    } catch (error) {
      console.error('Помилка отримання історії:', error)
    }
  }

  useEffect(() => {
    fetchHistory()

    socket.on('update-history', (newTask) => {
      fetchHistory()
    })

    return () => {
      socket.off('update-history')
    }
  }, [])

  const handleClearAllTasks = async () => {
    try {
      const response = await fetch('http://localhost:5002/api/clear-tasks', {
        method: 'DELETE',
      })

      if (response.status === 200) {
        const data = await response.json()
        setError(data.message)
      } else {
        const { message } = await response.json()
        setError(message)
      }
      fetchHistory()
    } catch (error) {
      setError('Не вдалося очистити задачі')
      console.error('Помилка запиту на очищення задач:', error)
    }
  }

  const handleSubmit = async (event) => {
    event.preventDefault()
    const file = event.target.elements.image.files[0]
    const formData = new FormData()
    formData.append('image', file)

    try {
      const response = await fetch('http://localhost:5002/api/recognize', {
        method: 'POST',
        body: formData,
      })
      if (response.status !== 200) {
        const { message } = await response.json()
        setError(message)
        return
      }
      const data = await response.json()
      const { jobId } = data

      setJobId(jobId)
      setError('')
      setResult('')
      setProgress(0)

      socket.emit('join', jobId)
      socket.on('progress', (info) => {
        setProgress(info.progress)
      })
      socket.on('result', (text) => {
        setResult(text)
        setProgress(null)
        socket.emit('update-history', { jobId, result: text, progress: 100 })
      })
      socket.on('error', (message) => {
        setError(message)
        setProgress(null)
      })
      socket.on('canceled', (message) => {
        setError(message)
        setProgress(null)
      })
    } catch (error) {
      setError('Помилка запиту')
      console.error('Помилка запиту:', error)
    }
  }

  const handleCancelHistoryTask = (jobId) => {
    fetch(`http://localhost:5002/api/cancel/${jobId}`, {
      method: 'POST',
    })
      .then((response) => response.json())
      .then((data) => {
        if (data.success) {
          setError('Задача скасована')
          io.emit('update-history')
        } else {
          setError('Не вдалося скасувати задачу')
        }
      })
      .catch((err) => {
        setError('Не вдалося скасувати задачу')
        console.error(err)
      })
  }

  const handleCancel = () => {
    if (jobId) {
      fetch(`http://localhost:5002/api/cancel/${jobId}`, {
        method: 'POST',
      })
        .then(() => {
          setError('Задача скасована')
          setProgress(null)
        })
        .catch((err) => {
          setError('Не вдалося скасувати задачу')
          console.error(err)
        })
    }
  }

  return (
    <Box
      display='flex'
      flexDirection='column'
      alignItems='center'
      gap={3}
      mt={5}
    >
      <Typography variant='h4' component='h1' gutterBottom>
        Розпізнавання рукописного тексту
      </Typography>

      <form
        onSubmit={handleSubmit}
        style={{
          display: 'flex',
          flexDirection: 'column',
          alignItems: 'center',
          gap: 16,
        }}
      >
        <Button
          variant='contained'
          component='label'
          color='primary'
          startIcon={<CloudUploadIcon />}
        >
          Завантажити зображення
          <input type='file' name='image' accept='image/*' hidden required />
        </Button>

        <Button variant='contained' type='submit' color='success'>
          Розпізнати текст
        </Button>
      </form>

      {progress !== null && (
        <Box display='flex' alignItems='center' gap={2}>
          <CircularProgress variant='determinate' value={progress * 100} />
          <Typography variant='body1'>
            Прогрес: {Math.round(progress * 100)}%
          </Typography>
          <Button variant='outlined' color='error' onClick={handleCancel}>
            Скасувати
          </Button>
        </Box>
      )}

      {result && (
        <Box mt={3} width='80%'>
          <Typography variant='h6'>Результат:</Typography>
          <TextField
            variant='outlined'
            fullWidth
            multiline
            rows={4}
            value={result}
            InputProps={{
              readOnly: true,
            }}
          />
        </Box>
      )}

      {error && (
        <Alert severity='error' style={{ marginTop: 16 }}>
          {error}
        </Alert>
      )}

      {history && history.length > 0 && (
        <Box mt={5} width='80%'>
          <Typography variant='h6' gutterBottom>
            Історія задач:
          </Typography>
          <List>
            {history.map((task) => (
              <ListItem
                key={task._id}
                sx={{
                  borderBottom: '1px solid #ddd',
                  paddingY: 2,
                  display: 'flex',
                  justifyContent: 'space-between',
                }}
              >
                <ListItemText
                  primary={
                    <Typography variant='body1'>
                      {task.jobId} - {task.status}
                    </Typography>
                  }
                  secondary={
                    task.resultText && (
                      <Typography
                        variant='body2'
                        sx={{ color: 'text.secondary' }}
                      >
                        {task.resultText}
                      </Typography>
                    )
                  }
                />
                {task.status === 'in_progress' && (
                  <Button
                    variant='outlined'
                    color='error'
                    size='small'
                    onClick={() => handleCancelHistoryTask(task.jobId)}
                  >
                    Скасувати
                  </Button>
                )}
              </ListItem>
            ))}
          </List>

          <Box mt={5}>
            <Button
              variant='outlined'
              color='secondary'
              onClick={handleClearAllTasks}
              sx={{ marginTop: 2 }}
            >
              Очистити всі задачі
            </Button>
          </Box>
        </Box>
      )}
    </Box>
  )
}

export default TextRecognition
