#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 30
#define HEIGHT 10

void draw(int playerX, int obsX, int obsY, int score, int lives) {
    int x, y;

    system("cls");

    printf("Simple Dodge Game\n");
    printf("Controls: A = left, D = right, Q = quit\n");
    printf("Score: %d   Lives: %d\n\n", score, lives);

    for (y = 0; y < HEIGHT; y++) {
        for (x = 0; x < WIDTH; x++) {

            if (y == HEIGHT - 1 && x == playerX) {
                // player on bottom row
                printf("P");
            } else if (y == obsY && x == obsX) {
                // obstacle
                printf("X");
            } else {
                printf(".");
            }
        }
        printf("\n");
    }
}

int main() {
    int playerX;            // player horizontal position
    int obsX, obsY;         // obstacle position
    int score;
    int lives;
    int gameOver;
    int speed;              // sleep time in ms (lower = faster)
    char ch;
    char playAgain;

    srand((unsigned int)time(NULL));

    do {
        // reset values for new game
        playerX = WIDTH / 2;
        obsX = rand() % WIDTH;
        obsY = 0;
        score = 0;
        lives = 3;
        speed = 120;       // starting speed
        gameOver = 0;

        while (!gameOver) {

            // handle input (non-blocking)
            if (_kbhit()) {
                ch = _getch();
                if (ch == 'a' || ch == 'A') {
                    playerX--;
                } else if (ch == 'd' || ch == 'D') {
                    playerX++;
                } else if (ch == 'q' || ch == 'Q') {
                    gameOver = 1;
                }
            }

            // keep player inside screen
            if (playerX < 0) playerX = 0;
            if (playerX >= WIDTH) playerX = WIDTH - 1;

            // move obstacle down
            obsY++;

            // when obstacle reaches bottom, respawn at top and increase score
            if (obsY >= HEIGHT) {
                obsY = 0;
                obsX = rand() % WIDTH;
                score += 10;

                // difficulty: every 50 points, increase speed
                if (score % 50 == 0 && speed > 40) {
                    speed -= 10;
                }
            }

            // check collision (same column on bottom row)
            if (obsY == HEIGHT - 1 && obsX == playerX) {
                lives--;

                if (lives <= 0) {
                    gameOver = 1;
                } else {
                    // reset obstacle after losing a life
                    obsY = 0;
                    obsX = rand() % WIDTH;
                }
            }

            draw(playerX, obsX, obsY, score, lives);
            Sleep(speed);
        }

        system("cls");
        printf("Game Over!\n");
        printf("Final Score: %d\n", score);
        printf("Play again? (y/n): ");
        scanf(" %c", &playAgain);

    } while (playAgain == 'y' || playAgain == 'Y');

    printf("Thanks for playing!\n");
    return 0;
}
