let currentGameId = null;

async function startNewGame() {
    try {
        const response = await fetch('http://localhost:3000/new-game', {
            method: 'POST'
        });
        const data = await response.json();
        currentGameId = data.gameId;
        
        // Reset UI
        document.getElementById('message').classList.add('hidden');
        document.getElementById('attempts').classList.add('hidden');
        document.getElementById('guess-input').value = '';
        document.getElementById('guess-input').focus();
    } catch (error) {
        console.error('Error starting new game:', error);
    }
}

async function makeGuess() {
    if (!currentGameId) {
        alert('Please start a new game first!');
        return;
    }

    const guessInput = document.getElementById('guess-input');
    const guess = parseInt(guessInput.value);

    if (isNaN(guess) || guess < 1 || guess > 100) {
        alert('Please enter a valid number between 1 and 100');
        return;
    }

    try {
        const response = await fetch('http://localhost:3000/guess', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({
                gameId: currentGameId,
                guess: guess
            })
        });

        const data = await response.json();
        
        const messageElement = document.getElementById('message');
        const attemptsElement = document.getElementById('attempts');
        
        messageElement.textContent = data.message;
        messageElement.classList.remove('hidden');
        messageElement.className = data.won ? 'message-success' : 'message-error';
        
        attemptsElement.textContent = `Attempts: ${data.attempts}`;
        attemptsElement.classList.remove('hidden');

        if (data.won) {
            currentGameId = null;
        }

        guessInput.value = '';
        guessInput.focus();
    } catch (error) {
        console.error('Error making guess:', error);
    }
}

// Start a new game when the page loads
window.onload = startNewGame;

// Allow pressing Enter to make a guess
document.getElementById('guess-input').addEventListener('keypress', function(e) {
    if (e.key === 'Enter') {
        makeGuess();
    }
}); 