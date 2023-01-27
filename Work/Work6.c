//
// Created by Даниил on 19.09.2022.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


struct st1 {
    int i;
    char c[128];
};

void st_rand(struct st1 *tmp) {
    int j;
    tmp->i = rand() % 100;
    for (j = 0; j < 128; j++) {
        tmp->c[j] = (char) (rand() % 26 + 65);
    }

}
void sort_f(struct st1 *p, int n) {
    int i, j;
    struct st1 temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if ((p + j)->i > (p + j + 1)->i) {
              // printf("%d %d \n",(p + j)->i,(p + j + 1)->i );
                temp = *(p + j);
                *(p + j) = *(p + j + 1);
                *(p + j + 1) = temp;
            }
        }
    }
}
int bin_search(struct st1 *mas, int n, int key){
  // printf("%d %d \n", *mas, n );
  int mid;
  mid = (mas+n/2)->i;
  if (mid==key){
    return 1;
  }
  if (mas->i>=(mas+n/2)->i){
      return 0;
    }
  if (mid>key){
    bin_search(mas, n/2, key);
  } else{
    bin_search(mas+n/2, n-n/2, key);
  }
}
void mout(struct st1 *p, int n){
  int i;
  for (i=0;i<n;i++){
      printf("%d\n", (p+i)->i);
      printf("%s\0\n", (p+i)->c);
      printf("\n");
  }
  printf("---------\n");
}

int main(int argc, char * argv[]) {
    struct st1 *pq;
    int i;
    // int n=atoi(argv[1]);
    int n=10;
    if ((pq = malloc(n * sizeof(struct st1))) == NULL) {
        printf("malloc: NULL\n");
        exit(1);
    }
    for (i=0;i<n;i++){
        st_rand((pq+i ));
    }

    mout(pq,n);
    sort_f(pq,n);
    mout(pq,n);

    printf("%d %d \n", bin_search(pq,n,(pq+n-1)->i),(pq+n-1)->i);
    // printf("%d %d \n", bin_search(pq,n,13),13);
    return 0;
}
