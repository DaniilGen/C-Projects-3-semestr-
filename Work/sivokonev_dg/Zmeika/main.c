#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <time.h>
#include "Snake.h"


int main(int argc, char *argv[]){
  clrscr();
  Game();
  return 0;
}
