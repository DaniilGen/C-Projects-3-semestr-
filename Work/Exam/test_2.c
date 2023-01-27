#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <signal.h>
#include <poll.h>

char *swapl(char *s){
  char *ok=s;
  while(*s!='\0'){
    if (*s>=65 && *s<=90){
      *s+=32;
    }
    s++;
  }
  return ok;
}

int main(){
  char str1[]="POrls";
  char *str2="POrls";

  char *p1,*p2;
  p1=str1;
  p2=str2;


  printf("%p \n", p1);
  printf("%p \n", p2);
  *p1='x';
  ***p2='x';
  printf("%s \n", p1);
  printf("%s \n", p2);
  // char *lp;
  // printf("%s \n", str );
  // lp=swapl(str);
  // printf("%s \n", lp );
}
