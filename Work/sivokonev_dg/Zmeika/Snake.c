#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <time.h>
#include "Snake.h"

struct termios orig_termios;

void push_body(Snake **snake, int x, int y){
  Snake *tmp=NULL;
  if ((tmp=malloc(sizeof(Snake)))==NULL){
    exit(1);
  }
  tmp->x=x;
  tmp->y=y;

  if (snake==NULL){
    tmp->next=NULL;
  } else{
    tmp->next=*snake;
  }

  *snake=tmp;
}

int len(Snake *snake){
  Snake *tmp;
  int kol=0;
  tmp=snake;

  while (tmp!=NULL){
    kol++;
    tmp=tmp->next;
  }

  return kol;
}


Snake *get_head(Snake *snake){
  Snake *tmp;
  tmp=snake;

  while (tmp->next!=NULL){
    tmp=tmp->next;

  }

  return tmp;
}


void clrscr(void)
{
    clear();
}

void gotoxy(int x,int y)
{
  printf("%c[%d;%df",0x1B,y,x);
}

void OffCanon(){
  struct termios raw;
  tcgetattr(STDIN_FILENO,&orig_termios);
  raw=orig_termios;
  raw.c_lflag &=~(ECHO | ICANON | O_NONBLOCK );
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}
void OnCanon(){
  struct termios raw;
  tcgetattr(STDIN_FILENO,&orig_termios);
  raw=orig_termios;
  raw.c_lflag |=(ECHO | ICANON );
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
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
    char c;
    char b[5];

    c=read(STDIN_FILENO,b,5);
    if (c==3){
    if (b[0]==0x1b && b[1]==0x5b && b[2] == 0x41 ) {
      direction_new=4;
    } else if (b[0]==0x1b && b[1]==0x5b && b[2] == 0x42 ) {
      direction_new=3;
    } else if (b[0]==0x1b && b[1]==0x5b && b[2] == 0x43) {
      direction_new=1;
    } else if (b[0]==0x1b && b[1]==0x5b && b[2] == 0x44) {
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

void CheckLoss(Snake *snake){
  int i,j,error=0;
  Snake *tmp, *tmp1;
  if (get_head(snake)->x == 1 || get_head(snake)->x ==consoleWidth) {
    clrscr();
    OnCanon();
    printf("SRY, YOU LOST :((" );
    exit(0);
  }
  if (get_head(snake)->y ==1 || get_head(snake)->y ==consoleHeight) {
    clrscr();
    OnCanon();
    printf("SRY, YOU LOST :((" );
    exit(0);
  }

  tmp=snake;
  while (tmp->next!=NULL){
    tmp1=tmp->next;
    while (tmp1!=NULL){

      if (tmp->x==tmp1->x && tmp->y==tmp1->y){
        clrscr();
        OnCanon();
        printf("SRY, YOU LOST :((" );
        exit(0);
      }

      tmp1=tmp1->next;
    }
    tmp=tmp->next;
  }

}


void moveSnake(Snake *snake, int direction){
  Snake *tmp=NULL,*head=get_head(snake);
  int i;

  gotoxy(snake->x,snake->y);
	printf("%c",'.');

  if (len(snake)>1){
    gotoxy(head->x,head->y);
    printf("%c",'%');
  }

  tmp=snake;

  while (tmp->next!=NULL){
    tmp->x=tmp->next->x;
    tmp->y=tmp->next->y;
    tmp=tmp->next;
  }

  switch (direction) {
    case 1:
    head->x++;
    break;
    case 2:
    head->x--;
    break;
    case 3:
    head->y++;
    break;
    case 4:
    head->y--;
    break;
  }

  gotoxy(head->x,head->y);
  printf("%c",'@');
}
void GenerateFood(Apple *apple){
  srand ( time(NULL) );
  apple->x = rand() % (consoleWidth-2)+2;
  srand ( time(NULL) );
  apple->y = rand() % (consoleHeight-2)+2;
  gotoxy(apple->x,apple->y);
  printf("%c",'+');
}

int CheckApple (Snake *snake, Apple apple){
  if (get_head(snake)->x==apple.x && get_head(snake)->y==apple.y){
    return 1;
  } else{
    return 0;
  }
}
void Game(){
  Snake *snake=NULL;
  Apple apple;
  int direction=1, direction_temp, rating=0, can=1, old;
  char c;
  fcntl(0, F_SETFL, fcntl(0, F_GETFL) | O_NONBLOCK);
  OffCanon();
  Walls();
  printSnake();
  push_body(&snake,first_pos_x,first_pos_y);
  apple.x=0;
  apple.y=0;
  GenerateFood(&apple);
  while (GameStop(rating)!=1){
    if(can)
		{
			old = direction;
			direction = button(direction);
		}

		if(old != direction)
			can = 0;
    printf("\n"); // ???
    direction=button(direction);
    moveSnake(snake,direction);
    can=1;
    CheckLoss(snake);

    if (CheckApple(snake, apple)){
      GenerateFood(&apple);
      push_body(&snake,0,0);
      rating++;
    }
    usleep(SPEED/6);
  }

}
