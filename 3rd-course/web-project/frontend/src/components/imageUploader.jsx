import React, { useState } from 'react';
import { Box, Button, CircularProgress, TextField, Typography, Alert } from '@mui/material';
import { CloudUpload as CloudUploadIcon } from '@mui/icons-material';
import io from 'socket.io-client';

const socket = io('http://localhost:5000');

function TextRecognition() {
    const [progress, setProgress] = useState(null);
    const [result, setResult] = useState('');
    const [error, setError] = useState('');

    const handleSubmit = async (event) => {
        event.preventDefault();
        const file = event.target.elements.image.files[0];
        const formData = new FormData();
        formData.append('image', file);

        try {
            const response = await fetch('http://localhost:5000/api/recognize', {
                method: 'POST',
                body: formData,
            });

            const data = await response.json();
            const { jobId } = data;

            socket.emit('join', jobId);

            socket.on('progress', (info) => {
                setProgress(info.progress);
            });

            socket.on('result', (text) => {
                setResult(text);
                setProgress(null);
            });

            socket.on('error', (message) => {
                setError(message);
            });

        } catch (error) {
            setError('Помилка запиту');
            console.error('Помилка запиту:', error);
        }
    };

    return (
        <Box display="flex" flexDirection="column" alignItems="center" gap={3} mt={5}>
            <Typography variant="h4" component="h1" gutterBottom>
                Розпізнавання рукописного тексту
            </Typography>
            
            <form onSubmit={handleSubmit} style={{ display: 'flex', flexDirection: 'column', alignItems: 'center', gap: 16 }}>
                <Button
                    variant="contained"
                    component="label"
                    color="primary"
                    startIcon={<CloudUploadIcon />}
                >
                    Завантажити зображення
                    <input type="file" name="image" accept="image/*" hidden required />
                </Button>
                
                <Button variant="contained" type="submit" color="success">
                    Розпізнати текст
                </Button>
            </form>

            {progress !== null && (
                <Box display="flex" alignItems="center" gap={2}>
                    <CircularProgress variant="determinate" value={progress * 100} />
                    <Typography variant="body1">Прогрес: {Math.round(progress * 100)}%</Typography>
                </Box>
            )}

            {result && (
                <Box mt={3} width="80%">
                    <Typography variant="h6">Результат:</Typography>
                    <TextField
                        variant="outlined"
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
                <Alert severity="error" style={{ marginTop: 16 }}>
                    {error}
                </Alert>
            )}
        </Box>
    );
}

export default TextRecognition;
