//
// Created by Даниил on 19.09.2022.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 10

void reverse(int * mas, int n){
  int i, temp;
  for(i=0;i<n/2+n%2;i++){
    temp=*(mas+i);
    *(mas+i)=*(mas+n-i-1);
    *(mas+n-i-1)=temp;
  }
}
int * reverse2(int *mas, int n){
  int *begin;
  if ((begin= malloc(N*sizeof (int)))==NULL){
      printf("malloc: NULL\n");
      exit(1);
  }
  int i, temp;
  for(i=0;i<n/2+n%2;i++){
    *(begin+i)=*(mas+n-i-1);
    *(begin+n-i-1)=*(mas+i);
  }
  return begin;
}
void arr(int *p, int n) {
    int i;
    printf("%p\n", p);
    for (i = 0; i < n; i++, *p++ = rand() % 100);
}
int pr1(int *p, int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("[%d]@[%p]\n", *(p + i), (p + i));
    }
}
int main(int argc, char * argv[]) {
  int *a, *b;
  if ((a= malloc(N*sizeof (int)))==NULL){
      printf("malloc: NULL\n");
      exit(1);
  }

  arr(a,N);
  printf("---------\n");
  pr1(a,N);
  // reverse(a,N);
  // printf("---------\n");
  // pr1(a,N);
  b=reverse2(a,N);
  printf("---------\n");
  pr1(b,N);
    return 0;
}
