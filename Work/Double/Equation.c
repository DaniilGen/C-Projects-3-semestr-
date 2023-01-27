#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
  double a,b,c,diskr,x1,x2;
  scanf("%lf %lf %lf",&a,&b,&c );
  // printf("%lf %lf %lf \n",a,b,c  );
  diskr=b*b-4*a*c;
  // printf("%lf\n",diskr );
  if (diskr<0){
    printf("Решений в действительных числах нет\n");
    exit(0);
  }
  // diskr=sqrt(diskr);
  // printf("%lf\n",diskr );
  // printf("%lf \n", sqrt(diskr));
  x1=((-b)+sqrt(diskr))/(2.0*a);
  x2=((-b)-sqrt(diskr))/(2.0*a);
  // printf("Два решения x1, x2: %lf , %lf \n",x1,x2 );
  if (x1==x2){
    printf("Одно решение x: %lf \n",x1 );
  } else{
    printf("Два решения x1, x2: %lf , %lf \n",x1,x2 );

  }
}
