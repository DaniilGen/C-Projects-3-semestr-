#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <time.h>


#define consoleWidth 60
#define consoleHeight 15
#define first_pos_x consoleWidth/2
#define first_pos_y consoleHeight/2
#define SPEED (1000000)
#define clear() write(STDIN_FILENO, "\033[H\033[J", 6)


typedef struct Snake{
  int x;
  int y;
  struct Snake *next;
} Snake;

typedef struct Apple{
  int x;
  int y;
} Apple;


void push_body(Snake **snake, int x, int y);
int len(Snake *snake);
Snake *get_head(Snake *snake);
void clrscr(void);
void gotoxy(int x,int y);
void OffCanon();
void OnCanon();
void Walls();
void printSnake();
int GameStop(int rating);
int button(int direction);
void CheckLoss(Snake *snake);
void moveSnake(Snake *snake, int direction);
void GenerateFood(Apple *apple);
int CheckApple (Snake *snake, Apple apple);
void Game();
