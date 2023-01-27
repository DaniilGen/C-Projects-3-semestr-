#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <limits.h>
#include "Stack.h"

void solve(int kol, Stack **t1,Stack **t2,Stack **t3){
  printf("-----------------------------------------------------------------\n" );
  printf("Tower 1: \n" );
  printstack(*t1);
  printf("Tower 2: \n" );
  printstack(*t2);
  printf("Tower 3: \n" );
  printstack(*t3);
  if (kol==1){
    push(t3,pop(t1));
  } else{
    solve(kol-1,t1,t3,t2);
    solve(1,t1,t2,t3);
    solve(kol-1,t2,t1,t3);
  }
}

int main(int argc, char * argv[]) {
  Stack *t1,*t2,*t3;
  char tmp;
  int i=1,kol;
  sscanf(argv[1],"%d",&kol);
  for(i=kol;i>0;i--){
    printf("%d\n",i );
    push(&t1,i);
  }
  printf("Tower 1: \n" );
  printstack(t1);
  solve(kol,&t1,&t2,&t3);
  printf("Tower 1: \n" );
  printstack(t1);
  printf("Tower 2: \n" );
  printstack(t2);
  printf("Tower 3: \n" );
  printstack(t3);
  return 0;
}
