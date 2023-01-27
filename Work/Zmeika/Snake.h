#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <time.h>

// struct termios orig_termios;

#define consoleWidth 60
#define consoleHeight 15
#define first_pos_x consoleWidth/2
#define first_pos_y consoleHeight/2
#define SNAKE_SIZE 900
#define SPEED (1000000)

typedef struct Snake {
    int x;
    int y;
    int length;
} Snake;

void clrscr(void);
void gotoxy(int x,int y);
void OffCanon();
void OnCanon();
int kbhit(void);
void Walls();
void printSnake ();
int GameStop(int rating);
void CheckLoss(Snake snake[SNAKE_SIZE]);
void GenerateFood(Snake food[1]);
int CheckApple (Snake snake[SNAKE_SIZE], Snake food[1]);
void Game();
