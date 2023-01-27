//
// Created by Даниил on 19.09.2022.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int bin_search(int *mas,int n, int key){
  int mid;
  mid = *(mas+n/2);
  if (mid==key){
    return 1;
  }
  if (*mas>=*(mas+n/2)){
    return 0;
  }
  if (mid>key){
    bin_search(mas, n/2, key);
  } else{
    bin_search(mas+n/2, n-n/2, key);
  }
}

int main(int argc, char * argv[]) {
    int a[10]={ 1,2,3,5,5,6,7,8,9,10};
    int *p=a;
    int ans;
    ans=bin_search(p,10,10);
    printf("%d\n", ans);
    return 0;
}
