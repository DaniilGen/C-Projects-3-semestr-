#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int v;
    int ves;
    struct Node *next;
    struct Node *prev;
} node;

void printlist(node *tmp, int v){
  while(tmp!=NULL){
    printf("%d -> %d ves: %d\n", v, tmp->v, tmp->ves);
    tmp=tmp->next;
  }
}

node *add_head(node *head, int v, int ves){
    node *tmp=NULL;
    if((tmp=malloc(sizeof(node))) == NULL){
        perror("malloc: NULL");
        exit(1);
    }
    tmp->v = v;
    tmp->ves = ves;
    if(head == NULL) {tmp->next = NULL;
      tmp->prev = NULL;}
    else {
        head->prev = tmp;

        tmp->next = head;
    }
    return tmp;
}

int size(char *name){
  FILE *fi;
  int length = 0, v1, v2, ves;

  if ((fi=fopen(name,"r"))==NULL) exit(2);

  while (fscanf(fi,"%d %d %d", &v1, &v2,  &ves)!= EOF){
  if (v1>length) length=v1;
  if (v2>length) length=v2;
  // printf("%d %d %d\n", v1, v2, ves);
  }
  fclose(fi);
  return length;
}

int bool(int size_, int mas_v[size_]){
  int i, flag = 0;
  for(i = 0; i< size_; i++){
    if(mas_v[i] == 1000){
      flag = 1;
      break;
    }
  }
  return flag;
}

void pr(int size_, node * mas[]){
  int i;
  for(i=0;i<size_;i++)
    printlist((mas[i]), i+1);
  printf("work!\n");
}

int find_min(int mas_v[], int mas_v_proy[], int size_){
  int i, min_ves = 1000, index;
  for(i = 0; i < size_; i++){
    if(mas_v[i] < min_ves && mas_v_proy[i] == 0){
      min_ves = mas_v[i]; index = i + 1;
    }
  }
  return index;
}

void graph(int size_, int mas_v[size_], node *mas[],
  int mas_v_proy[size_], int a, int b){
  int i , min_ves = 1000, cur, cur_ves = 0;
  node *tmp = NULL;

  while(bool(size_, mas_v) == 1){
    cur = find_min(mas_v, mas_v_proy, size_);
    mas_v_proy[cur-1] = 1;
    tmp = mas[cur-1];
    while (tmp != NULL) {
      if(mas_v[tmp->v - 1] > tmp->ves + mas_v[cur-1] && mas_v_proy[tmp->v - 1]==0)
        mas_v[tmp->v - 1] = tmp->ves + mas_v[cur-1];
        tmp = tmp->next;
    }
    // tmp = mas[cur-1];
    // while (tmp != NULL) {
    //   if(mas_v[tmp->v - 1] < min_ves && mas_v_proy[tmp->v - 1]==0)
    //     min_ves = mas_v[tmp->v - 1];
    //     tmp = tmp->next;
    // }
    // cur_ves = min_ves;
    // cur = find_min(mas_v, mas_v_proy, size_);
    // mas_v_proy[cur-1] = 1;
  }
  for(i = 0; i < size_; i++){
    printf("%d ", mas_v[i]);
  }
}

int main(int argc, char * argv[]) {
  FILE *fi;
  int d1, d2, ves, n = 0, a = *argv[2] - '0', b = *argv[3] - '0';
  int size_=size(argv[1]),i=0,j=0;
  node *  mas[size_];
  int mas_v[size_], mas_v_proy[size_];

  for(i = 0; i < size_; i++){
    mas[i]=NULL;
    mas_v[i] = 1000;
    mas_v_proy[i] = 0;
  }
  // mas_v_proy[a-1] = 1;
  mas_v[a-1] = 0;

  if ((fi=fopen(argv[1],"r"))==NULL) exit(2);
  while (fscanf(fi,"%d %d %d", &d1, &d2, &ves)!= EOF){
    mas[d1-1] = add_head(mas[d1-1], d2, ves);
  }
  for(i=0;i<size_;i++)
    printlist(mas[i], i+1);

  // pr(size_, mas);

  graph(size_, mas_v, mas, mas_v_proy, a, b);

  fclose(fi);

  return 0;
}
