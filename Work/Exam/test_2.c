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
  char str[]="POrls";
  char *lp;
  printf("%s \n", str );
  lp=swapl(str);
  printf("%s \n", lp );
}
