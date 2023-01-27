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

int main(int argc, char * argv[]) {
    struct st1 qq;
    struct st1 *pq;
    int i ,n=atoi(argv[1]);
    if ((pq = malloc(n * sizeof(struct st1))) == NULL) {
        printf("malloc: NULL\n");
        exit(1);
    }
    for (i=0;i<n;i++){
        st_rand((pq+i ));
    }

    for (i=0;i<n;i++){
        printf("%d\n", (pq+i)->i);
        printf("%s\0\n", (pq+i)->c);
        printf("\n");
    }
    return 0;
}
