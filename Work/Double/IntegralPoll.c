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

#define PROCESS_NUMBER 4
#define errExit(msg)    do { perror(msg); _exit(EXIT_FAILURE); } while (0)

void child_handler(int sig) {
    pid_t pid;
    while((pid = waitpid(-1, NULL, WNOHANG)) > 0);
}

double func(double x){
  double y=sin(x);
  return y;
}

int checkDouble(char *chislo){
  int i=0, tochki=0, error=0, digits=0;
  // printf("%s\n", chislo );
  // printf("%d\n", strlen(chislo));
  if (((int)chislo[0])==45){
    i++;
  }
  for(;i<strlen(chislo);i++){
    if (((int)chislo[i])==46){
      tochki++;
    } else{
      if ((((int)chislo[i])>47) && (((int)chislo[i])<58)){
        digits++;
      } else{
        error=1;
      }

    }
    // printf("[%d] %c [%d]\n",i,chislo[i],chislo[i] );
  }
  // printf("%d %d %d\n", error,tochki,digits);
  if (error==0 && tochki<2 && digits>0){
    return 1;
  }
  else{
    return 0;
  }
}

int checkLong(char *chislo){
  int i=0, error=0, digits=0;
  for(;i<strlen(chislo);i++){
      if ((((int)chislo[i])>47) && (((int)chislo[i])<58)){
        digits++;
      } else{
        error=1;
      }

    // printf("[%d] %c [%d]\n",i,chislo[i],chislo[i] );
  }
  // printf("%d %d %d\n", error,tochki,digits);
  if (error==0 && digits>0){
    return 1;
  }
  else{
    return 0;
  }
}

int main(int argc, char * argv[]){
  struct sigaction new_act, old_act;
  sigemptyset (&new_act.sa_mask);
  new_act.sa_flags = 0;
  new_act.sa_handler = child_handler;

  int pipefd[PROCESS_NUMBER][2];
  pid_t cpid[PROCESS_NUMBER];

  int nfds, num_open_fds;
  struct pollfd *pfds;
  int ready;

  unsigned char i;

  sigaction (SIGCHLD, &new_act, &old_act);

  long long int n;
  int j,rr;
  double a,b,sum=0, razbienie,iter,rez;

  if (argc!=4){
    printf("Неправильные данные (должно быть 3 числа) \n");
    exit(0);
  }
  if (checkLong(argv[1])!=1 ||checkDouble(argv[2])!=1 || checkDouble(argv[3])!=1 ){
    printf("Неправильно введенные числа \n" );
    exit(0);
  }

  n=atoll(argv[1]);
  a=atof(argv[2]);
  b=atof(argv[3]);

  printf("parametres : %lli %lf %lf \n ",n,a,b  );


  if (a>=b){
    printf("Неправильные границы \n" );
    exit(0);
  }

  if (n<0 || (a==0.0 && b==0.0) || n==0){
    printf("ERROR parametres \n" );
    exit(0);
  }


  razbienie=(b-a)/n;

  num_open_fds = nfds = PROCESS_NUMBER;
  pfds = calloc(nfds, sizeof(struct pollfd));

  if (pfds == NULL) errExit("calloc");

  for (j=0;j<PROCESS_NUMBER;j++){

    if (pipe(pipefd[j]) == -1) errExit("pipe");
    pfds[j].fd = pipefd[j][0];
    pfds[j].events = POLLIN;
    if ((cpid[j] = fork()) == -1) errExit("fork");

    if (cpid[j] == 0) {
      sum=0;
      iter=a+(((b-a)*j)/PROCESS_NUMBER);
      while(iter<(a+((b-a)*(j+1))/PROCESS_NUMBER)){
        sum+=razbienie*(func(iter));
        iter+=razbienie;
      }

      printf("[%lf : %lf] sum: %lf \n",(a+(((b-a)*j)/PROCESS_NUMBER)),(a+((b-a)*(j+1))/PROCESS_NUMBER) , sum );
      fflush(stdout);

       close(pipefd[j][0]);
       write(pipefd[j][1], &sum, 8);
       close(pipefd[j][1]);
       _exit(EXIT_SUCCESS);
    } else {
       close(pipefd[j][1]);
    }
  }

  sum=0;
  while (num_open_fds > 0) {

    for (i = 0; i < PROCESS_NUMBER; i++) pfds[i].revents=0;

    if ((ready = poll(pfds, nfds, -1)) == -1) {
      if (errno != EINTR){
        errExit("poll");
      }
}

    for (i = 0; i < PROCESS_NUMBER; i++) {
       if (pfds[i].revents != 0) {
          if (pfds[i].revents & POLLIN) {
             while ((rr=read(pfds[i].fd, &rez, 8)) > 0){
               sum+=rez;
             }
             printf("\n");
             fflush(stdout);
             if(rr < 0 ) errExit("read");
          } else
          if ((pfds[i].revents & POLLHUP)&& (~(pfds[i].revents & POLLIN))) {
            printf("closing [%d] %d %d\n",i,pipefd[i][0],pfds[i].fd);
             fflush(stdout);
             if (close(pfds[i].fd) < 0 ) errExit("close pfds");
             pfds[i].fd = -1;
             pfds[i].events=0;
             waitpid( -1, NULL, WNOHANG);
             num_open_fds--;
          }
       }
    }
  }
  printf("\nIntegral: %lf \n",sum );

    exit(EXIT_SUCCESS);

}
