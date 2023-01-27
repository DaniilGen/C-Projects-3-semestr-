#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <time.h>
#include "Snake.h"

struct termios orig_termios;


void clrscr(void)
{
    system("clear");
}

void gotoxy(int x,int y)
{
  printf("%c[%d;%df",0x1B,y,x);
}

void OffCanon(){
  struct termios raw;
  tcgetattr(STDIN_FILENO,&orig_termios);
  raw=orig_termios;
  raw.c_lflag &=~(ECHO | ICANON);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}
void OnCanon(){
  struct termios raw;
  tcgetattr(STDIN_FILENO,&orig_termios);
  raw=orig_termios;
  raw.c_lflag |=(ECHO | ICANON);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}
int kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

  ch = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);

  if(ch != EOF)
  {
  ungetc(ch, stdin);
  return 1;
  }

  return 0;
}
void Walls(){
  int i,j;
  for (i=0;i<=consoleHeight;i++){
    gotoxy(0,i);
    printf("#");
    gotoxy(consoleWidth,i);
    printf("#");

  }

  for (i=0;i<=consoleWidth;i++){
    gotoxy(i,0);
    printf("#");

    gotoxy(i,consoleHeight);
    printf("#");

  }
  for (i=2;i<consoleWidth;i++){
    for (j=2;j<consoleHeight;j++){
    gotoxy(i,j);
    printf(".");
  }
}

}

void printSnake (){
  gotoxy(consoleWidth/2,consoleHeight/2);
  printf("@");

}

int GameStop(int rating){
  if (rating == 10){
    clrscr();
    OnCanon();
    printf("YOOUUU WIIINNN!!! \n" );
    printf("your rate %d ", rating );
    exit(0);
  }
  return 0;
}

int button(int direction){
  int direction_new=direction;
    if(kbhit())
  	{
  		int ch=getchar();

    if (ch == 0x41 ) {
      direction_new=4;
    } else if (ch == 0x42 ) {
      direction_new=3;
    } else if (ch == 0x43) {
      direction_new=1;
    } else if (ch == 0x44) {
      direction_new=2;
    }
  }
  if (direction_new!=direction){
    return direction_new;
  }
  else {
    return direction;
  }
}

void CheckLoss(Snake snake[SNAKE_SIZE]){
  int i,j,error=0;
  if (snake[0].x ==1 || snake[0].x ==consoleWidth) {
    clrscr();
    OnCanon();
    printf("SRY, YOU LOST :((" );
    exit(0);
  }
  if (snake[0].y ==1 || snake[0].y ==consoleHeight) {
    clrscr();
    OnCanon();
    printf("SRY, YOU LOST :((" );
    exit(0);
  }
  for (i = 0; i < snake[0].length; i++)
	{
    for (j = i+1; j < snake[0].length; j++){
      if (snake[i].x==snake[j].x && snake[i].y==snake[j].y){
        clrscr();
        OnCanon();
        printf("SRY, YOU LOST :((" );
        exit(0);
      }
    }
	}
}

void moveSnake(Snake snake[SNAKE_SIZE], int direction){
  int i;

  gotoxy(snake[snake[0].length-1].x,snake[snake[0].length-1].y);
	printf("%c",'.');

  if (snake[0].length>1){
    gotoxy(snake[0].x,snake[0].y);
    printf("%c",'%');
  }

	for( i = snake[0].length-1; i >= 1; i-- )
	{
		snake[i].x = snake[i-1].x;
		snake[i].y = snake[i-1].y;
	}

  switch (direction) {
    case 1:
    snake[0].x++;
    break;
    case 2:
    snake[0].x--;
    break;
    case 3:
    snake[0].y++;
    break;
    case 4:
    snake[0].y--;
    break;
  }

  gotoxy(snake[0].x,snake[0].y);
  printf("%c",'@');
}
void GenerateFood(Snake food[1]){
  srand ( time(NULL) );
  food[0].x = rand() % (consoleWidth-2)+2;
  srand ( time(NULL) );
  food[0].y = rand() % (consoleHeight-2)+2;
  gotoxy(food[0].x,food[0].y);
  printf("%c",'+');
}

int CheckApple (Snake snake[SNAKE_SIZE], Snake food[1]){
  if (snake[0].x==food[0].x && snake[0].y==food[0].y){
    return 1;
  } else{
    return 0;
  }
}
void Game(){
  Snake snake[SNAKE_SIZE];
  Snake food[1];
  int direction=1, direction_temp, rating=0, can=1, old;
  char c;
  OffCanon();
  Walls();
  printSnake();
  snake[0].x=first_pos_x;
  snake[0].y=first_pos_y;
  snake[0].length=1;
  food[0].x=0;
  food[0].y=0;
  GenerateFood(food);
  while (GameStop(rating)!=1){
    if(can)
		{
			old = direction;
			direction = button(direction);
		}

		if(old != direction)
			can = 0;

    direction=button(direction);
    moveSnake(snake,direction);
    can=1;
    CheckLoss(snake);
    if (CheckApple(snake, food)){
      GenerateFood(food);
      snake[0].length++;
      rating++;
    }
    usleep(SPEED/5);
  }

}
