//
// Created by Даниил on 19.09.2022.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int graph_size( char *name){
  FILE *input;
  int d1,d2,n=0;
  if ((input=fopen(name,"r"))==NULL) exit(2);
  while (fscanf(input,"%d %d", &d1, &d2)!= EOF){
    if (d1>n) n=d1;
    if (d2>n) n=d2;
    // printf("%d %d \n", d1, d2 );

}
fclose(input);
return n;
}

int main(int argc, char * argv[]) {
  // FILE *fi, *fo;
  FILE *input;
  int d1,d2,n=0;
  int m_size=graph_size(argv[1]),i=0,j=0;
  int mas[m_size][m_size];
  printf("%d\n", m_size );

  for(i=0;i<m_size;i++){
    for(j=0;j<m_size;j++){
      mas[i][j]=0;
      // printf("%d ", mas[i][j] );

}
// printf("------\n");

  }
  if ((input=fopen(argv[1],"r"))==NULL) exit(2);
  while (fscanf(input,"%d %d", &d1, &d2)!= EOF){
    mas[d1-1][d2-1]=1;
    // printf("%d\n",mas[d1-1][d2-1] );
    // printf("%d %d \n", d1-1, d2-1 );
}
for(i=0;i<m_size;i++){
  for(j=0;j<m_size;j++){
    printf("%d ", mas[i][j] );
}
printf("\n");

}
fclose(input);

    return 0;
}
