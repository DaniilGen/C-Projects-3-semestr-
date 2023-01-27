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

#define PROCESS_NUMBER 3
#define errExit(msg) do { perror(msg); _exit(EXIT_FAILURE); } while (0)

void child_handler(int sig) {
pid_t pid;
while((pid = waitpid(-1, NULL, WNOHANG)) > 0);
}

double func(double x){
double y=sin(x);
return y;
}

int main(){

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

long long n;
int j,rr;
double a,b,sum=0, razbienie,iter,rez;
scanf("%d %lf %lf",&n,&a,&b );
razbienie=(b-a)/n;

num_open_fds = nfds = PROCESS_NUMBER;
pfds = calloc(nfds, sizeof(struct pollfd));
if (pfds == NULL) errExit("malloc");

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

printf("sum: %d %lf \n",cpid[j], sum );
fflush(stdout);

close(pipefd[j][0]);
write(pipefd[j][1], &sum, 8);
close(pipefd[j][1]);
_exit(EXIT_SUCCESS);
} else {
close(pipefd[j][1]);
}
}

sleep(7);
sum=0;
while (num_open_fds > 0) {

for (i = 0; i < PROCESS_NUMBER; i++) pfds[i].revents=0;

if ((ready = poll(pfds, nfds, -1)) == -1) {
if (errno!=EINTR){
errExit("poll");}
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
if ((pfds[i].revents & POLLHUP)&&~(pfds[i].revents & POLLIN)) {
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
printf("\nIntegral: %lf \n",sum );

exit(EXIT_SUCCESS);

}
