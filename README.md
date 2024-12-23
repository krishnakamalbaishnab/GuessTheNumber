# Number Guessing Game

A web-based number guessing game with a C++ backend and modern web frontend. The game generates a random number between 1 and 100, and players try to guess it with feedback after each attempt.

## Features

- C++ backend using Crow framework
- Modern web frontend with Tailwind CSS
- Real-time feedback on guesses
- Attempt tracking
- Keyboard support (Enter to submit)
- Clean and responsive UI

## Prerequisites

### Backend
- C++ compiler (Visual Studio 2019 or later recommended for Windows)
- CMake (version 3.10 or higher)
- Git

### Frontend
- Any modern web browser
- Python (optional, for running the development server)

## Project Structure 


number-guessing-game/
├── backend/
│ ├── CMakeLists.txt
│ └── src/
│ └── main.cpp
└── frontend/
├── index.html
├── styles.css
└── script.js


## Building and Running

### Backend Setup

1. Clone the repository:

```bash
git clone <repository-url>
cd number-guessing-game
```

2. Build the backend:

```bash
mkdir build
cd build
cmake ..
make
```

3. Run the backend server:

bash
.\Release\number_guessing_game.exe


The backend server will start on `http://localhost:3000`

### Frontend Setup

1. Using Python's built-in HTTP server:


bash
cd frontend
python -m http.server 8000


2. Open your web browser and navigate to:

```
http://localhost:8000
```



## How to Play

1. Open the game in your web browser
2. Enter a number between 1 and 100 in the input field
3. Click "Guess" or press Enter to submit your guess
4. The game will tell you if your guess is too high or too low
5. Keep guessing until you find the correct number
6. Click "New Game" to start a new game at any time

## API Endpoints

### POST /new-game
Starts a new game and returns a game ID.

### POST /guess
Makes a guess for the current game.

Request body: