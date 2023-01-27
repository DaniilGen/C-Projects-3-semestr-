#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#define PROCESS_NUMBER 3

double func(double x){
  double y=sin(x);
  return y;
}

int main(){
  long long n;
  // pid_t cpid[PROCESS_NUMBER];
  // int pipefd[PROCESS_NUMBER][2];
  int j;
  double a,b,sum=0, razbienie,i,rez;
  scanf("%d %lf %lf",&n,&a,&b );
  // printf("%s\n", );
  razbienie=(b-a)/n;
      i=a;
      while(i<b){
        // printf("%lf \n",sum);
        sum+=razbienie*(func(i));
        i+=razbienie;
      }

    printf("%lf \n",sum );
    return(0);

}
