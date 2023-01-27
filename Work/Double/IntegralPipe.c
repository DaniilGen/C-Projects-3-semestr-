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
  pid_t cpid[PROCESS_NUMBER];
  int pipefd[PROCESS_NUMBER][2];
  int j;
  double a,b,sum=0, razbienie,i,rez;
  scanf("%d %lf %lf",&n,&a,&b );
  // printf("%s\n", );
  razbienie=(b-a)/n;
  // printf("%lf \n", razbienie);
  for(j=0;j<PROCESS_NUMBER;j++){
    pipe(pipefd[j]);
    cpid[j]=fork();
    // printf("pr: %d %lf %lf\n", cpid[j],a,b );
    if (cpid[j]==0){

      sum=0;
      i=a+(((b-a)*j)/PROCESS_NUMBER);
      while(i<(a+((b-a)*(j+1))/PROCESS_NUMBER)){
        // printf("%lf \n",sum);
        sum+=razbienie*(func(i));
        i+=razbienie;
      }

      // printf("sum: %d %lf \n",cpid[j], sum );
      close(pipefd[j][0]);          /* Reader will see EOF */
      // char   *conversion = (char *)&sum;
      // write(pipefd[j][1], conversion, strlen (conversion));
      write(pipefd[j][1], &sum, sizeof(&sum));
      // write(pipefd[j][1], "\0" ,1);
      close(pipefd[j][1]);          /* Reader will see EOF */
      // wait(NULL);                /* Wait for child */
      exit(EXIT_SUCCESS);
      // return 0;
    }
    close(pipefd[j][1]);          /* Reader will see EOF */

  }
  for(j=0;j<PROCESS_NUMBER;j++)
  wait(NULL);

  printf("OOKKK\n" );
  sum=0;
  for(j=0;j<PROCESS_NUMBER;j++){
  while (read(pipefd[j][0], &rez, 8) > 0)
      sum+=rez;

      // printf("%lf\n", sum );
      close(pipefd[j][0]);
    }
  printf("%lf\n", sum );
  // printf("%d %d %d\n",cpid1,cpid2,cpid3 );
  // if (cpid1==0){
  // i=a;
  // while(i<b/3){
    // printf("%lf \n",i );
    // sum+=razbienie*(func(i));
    // i+=razbienie;
  // }
  // printf("%d \n",cpid1, sum );
  // return sum;
// }
// if (cpid1==0){
// i=a;
// while(i<b/3){
  // printf("%lf \n",i );
  // sum+=razbienie*(func(i));
  // i+=razbienie;
// }
// }

  // for(i=a;i<b;i+razbienie){

  // }
  // printf("%lf \n", sum );

}
