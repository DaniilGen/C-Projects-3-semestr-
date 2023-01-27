#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
  int ver;
  int ves;
  struct Node * next;
} node;

void push(node **head, int ver, int ves){
  node *t=NULL;
  if ((t=malloc(sizeof(node)))==NULL){
    exit(1);
  }
  t->ver=ver;
  t->ves=ves;
  if (head==NULL)    t->next=NULL;
  else t->next=*head;
  *head=t;
}


int main(int argc, char * argv[]) {
  FILE *f;
  int ver1,ver2,ves, mver=0,i, nach, kones;
  node *t;
  printf("Napishite dve vershini nachalo i kones \n");
  scanf("%d %d", &nach, &kones);

  if ((f=fopen(argv[1],"r"))==NULL)
  exit(2);


  while (fscanf(f,"%d %d %d", &ver1, &ver2,&ves)!= EOF){
    if (ver1>mver){
      mver=ver1;
    }
    else{
      if (ver2>mver)
      mver=ver2;
    }
}
mver=mver+1;
node *vershini[mver];
int rasstoynia[mver], obhod[mver], obratn[mver];
for(i=0;i<mver;i++) {vershini[i]=NULL; rasstoynia[i]=10000; obhod[i]=0; obratn[i]=10000;}

fseek(f,0,SEEK_SET);

while (fscanf(f,"%d %d %d", &ver1, &ver2,&ves)!= EOF){
  push(&vershini[ver1],ver2,ves);
}

printf("Spisok \n" );
for(i=0;i<mver;i++){
  t=vershini[i];
  while ( t!=NULL){
    printf("%d %d %d \n",i,t->ver,t->ves );
    t=t->next;
  }
}

int flag=1, iter=nach, min_rasstoynia;
rasstoynia[nach]=0;
while(flag){
  t=vershini[iter];
  min_rasstoynia=10000;
    while(t!=NULL){
      if ((rasstoynia[iter]+t->ves)<rasstoynia[t->ver]){
        rasstoynia[t->ver]=rasstoynia[iter]+t->ves;
        obratn[t->ver]=iter;
      }
      t=t->next;
  }
  obhod[iter]=1;
  for(i=0;i<mver;i++){
    if (obhod[i]==0 && rasstoynia[i]<min_rasstoynia){
      min_rasstoynia=rasstoynia[i];
      iter=i;
    }
  }
  if (min_rasstoynia==10000){
    flag=0;
  }
}

for(i=0;i<mver;i++){
  printf("ver(%d) rasstoynia(%d) ot ver(%d) \n", i, rasstoynia[i], nach);
}

int it=kones;
flag=1;
printf("puti ot %d do %d\n", kones, nach );
printf("%d\n",kones );
while (flag){

it=obratn[it];
if (it==10000){
  flag=1;
  break;
}
  printf("%d\n",  it);
}

}
