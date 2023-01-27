#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <time.h>
#define clear() write(STDIN_FILENO,"\033[H\033[J",6)
struct termios orig_termios;

typedef struct Game{
  int position_x;
  int position_y;
  struct Game *next;
  struct Game *prev;
} Game;

void OffCanon(){
  struct termios raw;

  tcgetattr(STDIN_FILENO, &orig_termios);
  raw = orig_termios;
  raw.c_lflag &=~ (ECHO | ICANON);
  tcsetattr(STDIN_FILENO, TCSAFLUSH , &raw );
  fcntl(0, F_SETFL, fcntl(0, F_GETFL) | O_NONBLOCK);
}

void OnCanon(){
  struct termios raw;

  tcgetattr(STDIN_FILENO, &orig_termios);
  raw = orig_termios;
  raw.c_lflag |=~ (ECHO | ICANON);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}



void snake(Game *head, char kuda, char field[20][70], int length){
  int kol=0;
  Game *okay=NULL, *last=head;
  field[head->position_y][head->position_x]=' ';

  while (last!=NULL){
    field[last->position_y][last->position_x]=' ';
    last=last->next;

  }
  last=head;
  while (last->next!=NULL){
    last=last->next;

  }

  while (last!=head){
    kol++;
    last->position_y=last->prev->position_y;
    last->position_x=last->prev->position_x;
    last=last->prev;
  }

  if (head->next!=NULL){
    okay=head->next;
    while (okay!=NULL){
     field[okay->position_y][okay->position_x]='o';
     okay=okay->next;
   }
  }


  switch (kuda) {
    case 'w':
    head->position_y--;
    break;
    case 's':
    head->position_y++;
    break;
    case 'a':
    head->position_x--;
    break;
    case 'd':
    head->position_x++;
    break;
  }

  field[head->position_y][head->position_x]='+';
}

Game *push(Game *head, int position_x, int position_y){
  Game *t=NULL, *t2=NULL;
  if ((t=malloc(sizeof(Game)))==NULL){
    exit(1);
  }

  t2=head;
  t->position_x=position_x;
  t->position_y=position_y;

  if (head==NULL){
    return t;
  }
  while (head->next!=NULL){
      head=head->next;
  }
  head->next=t;
  t->prev=head;
  return(t2);
}

Game * begin(Game *head, char field[20][70]){
  int i,j, position_x,position_y;

  for(i=0;i<20;i++)
  for(j=0;j<70;j++)
  field[i][j]=' ';

  for(i=0;i<70;i++){
    field[0][i]='V';
    field[19][i]='V';
  }

  for(i=0;i<20;i++){
    field[i][0]='V';
    field[i][69]='V';
  }
  srand ( time(NULL) );
  position_x= rand() % (66)+3;
  position_y= rand() % (16)+3;

  head=push(head,position_x,position_y);
  field[head->position_y][head->position_x]='+';
  return head;
}

void print_borders(char field[20][70]){
  int i,j;
  clear();
  for(i=0;i<20;i++){

  for(j=0;j<70;j++){
    printf("%c", field[i][j] );

  }
  printf("\n" );
}
}

void check(Game *head, char field[20][70], int score){
  if (head->position_x==0 || head->position_x==69 || head->position_y==0 || head->position_y==19){
    clear();
    printf("(((((PROIGRAL!)))))\n" );
    exit(0);
  }


  if (score==7){
    clear();
    printf("(((((POBEDA!)))))\n" );
    exit(0);
  }
}

void appple(char field[20][70], int *x_appple, int *y_appple){
  *x_appple= rand() % (66)+3;
  *y_appple= rand() % (16)+3;
  field[*y_appple][*x_appple]='a';
}

int main(int argc, char * argv[]) {
  int i,j, score=0, x_appple, y_appple, length=1;
  Game *head=NULL;
  char c,kuda='a', ok;
  char b[5], field[20][70];

  printf("Are you ready?? (Wait 5 seconds)\n" );
  sleep(5);

  OffCanon();
  clear();
  head=begin(head, field);
  appple(field,&x_appple,&y_appple);


  print_borders(field);
  while((c=getc(stdin))!='~'){
    switch (c) {
      case 'w':
      kuda='w';
      break;
      case 'd':
      kuda='d';
      break;
      case 's':
      kuda='s';
      break;
      case 'a':
      kuda='a';
      break;
    }

  snake(head,kuda,field,length);
  check(head,field,score);

  if (head->position_x==x_appple && head->position_y==y_appple){
    head=push(head,0,0);
    score=score+1;
    appple(field,&x_appple,&y_appple);
    length=length+1;
  }

  clear();
  print_borders(field);

  usleep(1000000/7);
  }

  return 0;
}
