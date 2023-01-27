#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <signal.h>
#include <poll.h>
#include <math.h>
#define NUM 3
#define errExit(msg)    do { perror(msg); _exit(EXIT_FAILURE); } while (0)

void child_handler(int sig) {
  pid_t pid;
  while((pid = waitpid(-1, NULL, WNOHANG)) > 0);
}

double function(double x){
  return cos(x);
}

int main(int argc, char *argv[]) {

  struct sigaction new_act, old_act;
  sigemptyset (&new_act.sa_mask);
  new_act.sa_flags = 0;
  new_act.sa_handler = child_handler;

  int pipefd[NUM][2];
  pid_t cpid[NUM];

  int nfds, num_open_fds;
  struct pollfd *pfds;
  int ready,rr;


  unsigned char i,tt;

  sigaction (SIGCHLD, &new_act, &old_act);


  double xi, ipp;
  int nx;
  double a, b;
  double s=0, si, okey=0, buf;

  printf("Введите интервал (а и в) и количество разбиений\n");
  scanf("%lf %lf %d", &a, &b, &nx);

  num_open_fds = nfds = NUM;
  pfds = calloc(nfds, sizeof(struct pollfd));
  if (pfds == NULL) errExit("malloc");

  xi = (b - a)/nx;

  for (i=0;i<NUM;i++){

    if (pipe(pipefd[i]) == -1) errExit("pipe");
    pfds[i].fd = pipefd[i][0];
    pfds[i].events = POLLIN;
    if ((cpid[i] = fork()) == -1) errExit("fork");

    if (cpid[i] == 0) {

      ipp= a + ((b-a)/NUM)*i;

      while(ipp<a+((b-a)/NUM)*(i+1)){
        si = xi * function(ipp);

        s += si;
        ipp+=xi;
      }

      close(pipefd[i][0]);
      write(pipefd[i][1], &s,8);
      close(pipefd[i][1]);
      _exit(EXIT_SUCCESS);
    } else {
      close(pipefd[i][1]);
    }
  }

  while (num_open_fds > 0) {
    printf("\ntry poll:\n");
    fflush(stdout);
    for (i = 0; i < NUM; i++) pfds[i].revents=0;


    if ((ready = poll(pfds, nfds, -1)) == -1){
      if (errno!=EINTR){
         errExit("poll");
      }
    }


    for (i = 0; i < NUM; i++) {
      if (pfds[i].revents != 0) {
              if (pfds[i].revents & POLLIN) {
                while ((rr=read(pfds[i].fd, &buf, 8)) > 0){
                  okey=okey+buf;
                }
                if(rr < 0 ) errExit("read");
              } else
              if ((pfds[i].revents & POLLHUP)&& (~(pfds[i].revents & POLLIN))) {
                printf("closing [%d] %d %d\n",i,pipefd[i][0],pfds[i].fd);
                fflush(stdout);
                if (close(pfds[i].fd) < 0 ) errExit("close pfds");
                pfds[i].fd = -1;
                pfds[i].events=0;
                num_open_fds--;
    }
 }
}
}


printf("rez  --  %lf \n", okey );

exit(EXIT_SUCCESS);
}
