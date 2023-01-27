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
    tmp->c[127]='\0';
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

void in(struct st1 *p, FILE *input, char *name){
  int kol=0;
  if ((input=fopen(name,"r"))==NULL) exit(2);
  while (fscanf(input,"%d %s", &(p+kol)->i, (p+kol)->c)!= EOF){
  kol++;
}
mout(p,kol);
fclose(input);
}

void out(struct st1 *p, FILE *output, char *name, int n){
  int i;
  if ((output=fopen(name,"w"))==NULL) exit(2);
  for (i=0;i<n;i++){
    fprintf(output, "%d %s \n", (p+i)->i, (p+i)->c );
  }
fclose(output);
}


int main(int argc, char * argv[]) {
  FILE *fi, *fo;
  int chislo;
  char stroka[128];
  struct st1 *st, *st2;
  int n=20,i,kol=0;

  // fseek(fi,0,SEEK_END);
  // printf("->%d\n", ftell(fi) );
  // rewind(fi);
  if ((st = malloc(n * sizeof(struct st1))) == NULL) {
      printf("malloc: NULL\n");
      exit(1);
  }
  if ((st2 = malloc(n * sizeof(struct st1))) == NULL) {
      printf("malloc: NULL\n");
      exit(1);
  }
  for (i=0;i<n;i++){
      st_rand((st+i ));
  }


  out(st,fo,argv[1],n);
  in(st2,fi,argv[1]);

    return 0;
}
