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

function TextRecognition() {
  const [progress, setProgress] = useState(null)
  const [result, setResult] = useState('')
  const [error, setError] = useState('')
  const [jobId, setJobId] = useState(null)
  const [history, setHistory] = useState([])
  const [isAuthenticated, setIsAuthenticated] = useState(
    localStorage.getItem('authToken') ? true : false
  )
  const [user, setUser] = useState({ username: '', password: '' })
  const [socket, setSocket] = useState(null)

  // отримує історію задач
  const fetchHistory = async () => {
    try {
      const response = await fetch('http://localhost:3015/api/history', {
        headers: {
          Authorization: `Bearer ${localStorage.getItem('authToken')}`,
        },
      })
      const data = await response.json()
      setHistory(data)
    } catch (error) {
      console.error('Помилка отримання історії:', error)
    }
  }

  // під'єднання сокета
  useEffect(() => {
    if (isAuthenticated) {
      fetchHistory()
      const newSocket = io('http://localhost:3001', {
        query: { token: localStorage.getItem('authToken') },
      })
      setSocket(newSocket)

      newSocket.on('update-history', () => {
        fetchHistory()
      })

      return () => {
        newSocket.disconnect()
      }
    }
  }, [isAuthenticated])

  const login = async () => {
    try {
      const formData = new FormData()
      formData.append('username', user.username)
      formData.append('password', user.password)

      const response = await fetch('http://localhost:3015/login', {
        method: 'POST',
        body: formData,
      })

      const data = await response.json()
      if (data.token) {
        localStorage.setItem('authToken', data.token)
        setIsAuthenticated(true)
        fetchHistory()
      }
    } catch (error) {
      setError('Не вдалося авторизуватися')
      console.error('Помилка авторизації:', error)
    }
  }

  const handleLogout = () => {
    localStorage.removeItem('authToken')
    setIsAuthenticated(false)
    setHistory([])
    setError('')
    setResult('')
    setProgress(null)

    if (socket) {
      socket.disconnect()
    }
  }

  const handleClearAllTasks = async () => {
    try {
      const response = await fetch('http://localhost:3015/api/clear-tasks', {
        method: 'DELETE',
        headers: {
          Authorization: `Bearer ${localStorage.getItem('authToken')}`,
        },
      })

      const data = await response.json()
      if (response.status === 200) {
        setError(data.message)
      } else {
        setError(data.message)
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
      const response = await fetch('http://localhost:3015/api/recognize', {
        method: 'POST',
        body: formData,
        headers: {
          Authorization: `Bearer ${localStorage.getItem('authToken')}`,
        },
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

      // оновлення результату та історії
      if (socket) {
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
      }
    } catch (error) {
      setError('Помилка запиту')
      console.error('Помилка запиту:', error)
    }
  }

  const handleCancelHistoryTask = (jobId) => {
    fetch(`http://localhost:3015/api/cancel/${jobId}`, {
      method: 'POST',
      headers: {
        Authorization: `Bearer ${localStorage.getItem('authToken')}`,
      },
    })
      .then((response) => response.json())
      .then((data) => {
        if (data.success) {
          setError('Задача скасована')
          if (socket) {
            socket.emit('update-history')
          }
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
      fetch(`http://localhost:3015/api/cancel/${jobId}`, {
        method: 'POST',
        headers: {
          Authorization: `Bearer ${localStorage.getItem('authToken')}`,
        },
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

      {!isAuthenticated ? (
        <Box>
          <TextField
            label='Username'
            value={user.username}
            onChange={(e) => setUser({ ...user, username: e.target.value })}
            fullWidth
            margin='normal'
          />
          <TextField
            label='Password'
            type='password'
            value={user.password}
            onChange={(e) => setUser({ ...user, password: e.target.value })}
            fullWidth
            margin='normal'
          />
          <Button variant='contained' color='primary' onClick={login}>
            Увійти
          </Button>
        </Box>
      ) : (
        <>
          <Button
            variant='outlined'
            color='secondary'
            onClick={handleLogout}
            sx={{ marginBottom: 2 }}
          >
            Вийти
          </Button>
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
              <input
                type='file'
                name='image'
                accept='image/*'
                hidden
                required
              />
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

          {error && <Alert severity='error'>{error}</Alert>}

          <Box mt={3} width='80%'>
            <Typography variant='h6'>Історія задач:</Typography>
            <Button variant='outlined' onClick={handleClearAllTasks}>
              Очистити всю історію
            </Button>
            <List>
              {history.map((task) => (
                <ListItem key={task.jobId}>
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
                      onClick={() => handleCancelHistoryTask(task.jobId)}
                    >
                      Скасувати
                    </Button>
                  )}
                </ListItem>
              ))}
            </List>
          </Box>
        </>
      )}
    </Box>
  )
}

export default TextRecognition
