# Game Analysis – Assignment 2

## 1. Game Overview

This project is a small console **dodge game** written in **C** for Windows.

The player controls a character `P` at the bottom of the screen. From the top, an obstacle `X` keeps falling. The main goal is to move left and right and avoid getting hit by the falling obstacle for as long as possible to increase your score.

---

## 2. Files and Structure

- `game.c` – main source file. Contains `main()` and the complete game logic (input, update, drawing, and game loop).
- `README.md` – explanation of how the game works and what changes I added for the assignment.

There are no extra header files. Everything is inside `game.c` to keep it simple.

---

## 3. Main Game Flow

Basic flow of the program:

1. Initialize all variables (player position, obstacle position, score, lives, speed, etc.).
2. Enter a **game loop** which keeps running until `gameOver` becomes true:
   - Read keyboard input (A/D to move, Q to quit).
   - Update player position and obstacle position.
   - Check for collision between player and obstacle.
   - Update score and difficulty.
   - Draw the current frame on the console.
3. When the player loses all lives or presses Q, the game loop ends and a **Game Over** message with final score is shown.
4. After that, the player can choose to **play again** or exit the program.

---

## 4. Important Variables and Functions

Some important variables in `game.c`:

- `int playerX;` – column position of the player `P` on the bottom row.
- `int obsX, obsY;` – column and row position of the falling obstacle `X`.
- `int score;` – stores the current score of the player.
- `int lives;` – number of lives left (starts from 3).
- `int speed;` – controls game speed using `Sleep(speed)` (smaller value = faster).
- `int gameOver;` – flag that decides when the inner game loop stops.

Important functions:

- `draw(...)` – clears the screen, prints header (controls, score, lives) and draws the game grid with `P` and `X`.
- `main()` – handles everything else:
  - initializes values,
  - contains the outer **play again** loop,
  - contains the main game loop where input, update, and collision are handled.

---

## 5. My Understanding of the Logic

In simple words, the game works like this:

1. Start the game and set default values (player in the middle, obstacle at top).
2. Keep running a loop where every frame:
   - If a key is pressed, move the player left or right.
   - Move the obstacle one step down.
   - If the obstacle reaches the bottom without hitting the player, increase the score and respawn the obstacle at the top.
   - If the obstacle hits the player, reduce one life.
3. If lives become zero, mark `gameOver = 1` and end the loop.
4. Show **Game Over** and ask if the player wants to try again.

This is the base logic on top of which I added my assignment features.

---

## 6. Modifications (Objective 2)

I implemented three required modifications in the existing game logic:

### 6.1 Score System

- Added a `score` variable that starts from 0.
- Every time the obstacle reaches the bottom without hitting the player, the score increases by 10.
- The current score is displayed at the top of the screen during the game.
- At the end, the final score is printed with the Game Over message.

### 6.2 Player Lives (3 chances)

- Introduced a `lives` variable, starting with 3.
- When the obstacle `X` collides with the player `P` on the bottom row:
  - `lives` is decreased by 1.
  - If lives are still greater than 0, the obstacle is reset and the game continues.
  - If lives become 0, `gameOver` is set and the game ends.
- The number of lives left is always shown on the top of the screen.

### 6.3 Game Restart Option

- Wrapped the whole game inside an outer `do { ... } while` loop.
- After Game Over, the program asks: **“Play again? (y/n):”**
- If the user presses `y` or `Y`:
  - score, lives, positions and speed are reset,
  - a new game starts immediately.
- If the user presses `n` or anything else, the program exits after printing a goodbye message.

### 6.4 Difficulty Increase (small extra improvement)

- The game speed is stored in the `speed` variable (used in `Sleep(speed)`).
- Every time the score reaches a multiple of 50, the `speed` value is decreased.
- This makes the obstacle fall faster as the player survives longer, so the game becomes gradually harder.

---

## 7. Controls and How to Play

- **A / a** – move player one step to the **left**.
- **D / d** – move player one step to the **right**.
- **Q / q** – quit the current game immediately.
- Avoid the `X` hitting your `P` at the bottom.
- You have **3 lives**. After that, it’s game over.
- At Game Over, press **y** to play again or **n** to exit.

---

## 8. How to Compile and Run (Windows)

1. Make sure you have a C compiler installed (e.g. MinGW).
2. Open Command Prompt in the project folder.
3. Compile:

   ```bash
   gcc game.c -o game.exe
