# Pac-Man Game on LandTiger LPC1768

Welcome to the implementation of the **Pac-Man** game on the ARM-based **LandTiger LPC1768** development board!  
This project features a full Pac-Man game with custom hardware-based gameplay and an AI-controlled ghost.

---

## 🎥 Gameplay Preview
Below is a demonstration of the gameplay running directly on the **LandTiger LPC1768**:

> **Note**: GitHub does not support direct playback of `.mp4` files within the README. To view the gameplay video, download the [PacmanGameplay.mp4](PacmanGameplay.mp4) file from this repository.

![Gameplay](PacmanGameplay.mp4)

---

## 🔧 Hardware Setup

The game is built for the **LandTiger LPC1768**, leveraging its onboard components to provide interactive and engaging gameplay.  
Key hardware used includes:

- **Joystick**: Controls Pac-Man's movements (up, down, left, right).
- **LCD Display**: Renders the labyrinth, pills, and characters in real-time.
- **LEDs**: Indicate in-game events, such as ghosts entering frightened mode.
- **Potentiometer**: Dynamically adjusts the randomization of pill placement and ghost behavior, adding an element of unpredictability to the gameplay.
- **Buttons**: Provide additional game controls, such as **Pause/Resume** and **Restart**.

---

## ✨ Core Features

### 🎮 Game Mechanics:
- **Pills and Scoring**:
  - Standard Pills increase score by 10 points.
  - Power Pills (randomly placed) increase score by 50 points and enable Pac-Man to eat ghosts.
- **Ghost AI**:
  - **Blinky** (red ghost) pursues Pac-Man using **Greedy Best-First Search Algorithm** for pathfinding.
  - Two distinct ghost behaviors:
    - **Chase Mode**: Follows Pac-Man's approximate position aggressively.
    - **Frightened Mode**: Activated after Pac-Man eats a Power Pill. Blinky runs away and can be eaten by Pac-Man.
- **Teleport Zones**: Pac-Man teleports across the board at specific central locations.
- **Lives and Progression**:
  - New life every 1000 points.
  - Victory condition: Eat all pills before the countdown timer reaches 0.
  - Game Over condition: Timer expires before clearing the labyrinth.

### 🔁 ARM-Specific Design:
- **Development Board**: Code optimized for the **LandTiger LPC1768**, ensuring smooth gameplay and seamless hardware interactions.
- **Timer and Interrupts**:
  - INT0: Pauses/resumes gameplay with a visual indication.
  - Countdown Timer: Starts at 60 seconds and decrements during play.
- **Potentiometer Integration**:
  - Changes the randomness of the game dynamically by varying values in the algorithms governing pill placement and ghost movements.

---

## 🧠 Ghost AI: Greedy Best-First Search

The ghost behavior relies on an efficient **Greedy Best-First Search (GBFS)** algorithm. Here’s how it works:
- In **Chase Mode**, the ghost calculates the Manhattan distance to the target position.
- In **Frightened Mode**, the ghost calculates the farthest position from Pac-Man's current location, creating a fleeing behavior.

The GBFS implementation allows the ghost to efficiently navigate the labyrinth while adapting to gameplay scenarios.
Additionally, as the game progresses, Blinky the ghost becomes faster and more aggressive. 

---

## 🎉 How to Play

1. Flash the program to your **LandTiger LPC1768** board.
2. Use the joystick to control Pac-Man and avoid the ghost.
3. Adjust the potentiometer to modify game randomness for a unique experience.
4. Press the buttons to pause, resume, or restart the game as needed.
5. Try to eat all pills or avoid getting caught to achieve victory!

Alternatively, use a simulator of LandTiger on IDE Keil uVision5. 

---