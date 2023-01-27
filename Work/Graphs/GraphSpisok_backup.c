#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <limits.h>

#define INF 1000000

typedef struct Node{
  int v1;
  int v2;
  int weight;
  struct Node *next;
  struct Node *prev;
} node;

node *add_head(node *head,int v1,int v2, int weight){
  node *tmp=NULL, *tmp1=NULL;
  if ((tmp=malloc(sizeof(node)))==NULL){
    exit(1);
  }
  if (head==NULL){
    tmp->v1=v1;
    tmp->v2=v2;
    tmp->weight=weight;
    tmp->next=NULL;
    tmp->prev=NULL;
    return tmp;
  }
  head->prev=tmp;

  tmp->v1=v1;
  tmp->v2=v2;
  tmp->weight=weight;

  tmp->prev=NULL;
  tmp->next=head;
  return(tmp);
}

node *del_head(node *head){
  node *tmp=NULL;
  if (head != NULL){
    tmp=head->next;
    tmp->prev=NULL;
    free(head);
  }
  return tmp;
}

node *add_tail(node *head, int v1,int v2, int weight){
  node *tmp=NULL, *tmp2=NULL;
  if ((tmp=malloc(sizeof(node)))==NULL){
    exit(1);
  }
  tmp2=head;
  tmp->v1=v1;
  tmp->v2=v2;
  tmp->weight=weight;
  while (head->next!=NULL){
      head=head->next;
  }
  head->next=tmp;
  tmp->prev=head;
  return(tmp2);
}


node *del_tail(node *head){
  node *tmp=NULL;
  tmp=head;
 while ((head->next)->next != NULL){
    head=head->next;
  }
  head->next=NULL;
  return tmp;
}
void printlist(node *head){
  node *tmp=NULL;
  tmp=head;
  printf("-------\n");
  while (tmp!=NULL){
    printf("[%d] -> [%d] : (%d) \n",tmp->v1+1, tmp->v2+1, tmp->weight);
    tmp=tmp->next;
  }
  printf("-------\n");
}

node *del(node *head, node *del){
  node *tmp1;
  tmp1=head;
  if (del==head){
    tmp1=head->next;
    tmp1->prev=NULL;
    return tmp1;
  }

  while (tmp1->next!=NULL && tmp1->next!=del){
    tmp1=tmp1->next;
  }
  if (tmp1){
    tmp1->next=tmp1->next->next;
    tmp1->prev=tmp1;
  }

  return head;
}

int length(node *head){
  node *tmp=NULL;
  int i=0;
  tmp=head;
  while (tmp!=NULL){
    i++;
    tmp=tmp->next;
  }
  return i;
}


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
  FILE *input;
  int d1,d2,d3,start,finish,vershina,ok,wt,min_dist, kol,i=0,j=0;
  int m_size=graph_size(argv[1]); // переменная, задающая размер графа через максимальный номер вершины
  node *mas[m_size], *tmp;
  printf("%d\n", m_size );
  printf("Vvedite start and finish \n");
  scanf("%d %d", &start, &finish);
  int dist[m_size], used[m_size], prev[m_size], path[m_size];
  for (i=0;i<m_size;i++){
    dist[i]=INF;
    prev[i]=-1;
    used[i]=0;
  }
  dist[start-1]=0;

  for(i=0;i<m_size;i++){
    mas[i]=NULL;
  }

  if ((input=fopen(argv[1],"r"))==NULL) exit(2);
  while (fscanf(input,"%d %d %d", &d1, &d2, &d3)!= EOF){
    mas[d1-1]=add_head(mas[d1-1],d1-1,d2-1,d3);
    // mas[d2-1]=add_head(mas[d2-1],d2-1,d1-1,d3); // можно оставить, если нужен неориентированный граф
  }

  for(i=0;i<m_size;i++){
    printlist(mas[i]);
  }

  min_dist=0;
  vershina=start-1;
  while (min_dist<INF){
    j=vershina;
    used[j]=1;
    tmp=mas[j];
    while (tmp!=NULL){
    ok=tmp->v2;
    wt=tmp->weight;
    if (dist[j]+wt<dist[ok]){
      dist[ok]=dist[j]+wt;
      prev[ok]=j;
    }
    tmp=tmp->next;
  }
  min_dist=INF;
  for (i=0;i < m_size; i++){
    if (!used[i] && dist[i]<min_dist){
      min_dist=dist[i];
      vershina=i;
    }
  }

}

if (dist[finish-1]==INF){
  printf("Vershina ne dostigima \n" );
  exit(0);
}

for(i=0;i<m_size;i++){
  printf("%d : (%d) \n",i+1, dist[i] );
}
kol=0;
path[kol]=finish;
vershina=finish-1;
while (vershina!=-1){
  kol++;
  vershina=prev[vershina];
  if (vershina!=-1)
  path[kol]=vershina+1;
}
printf("PATH: from %d to %d ves(%d) :\n", start, finish, dist[finish-1] );
for(i=kol-1;i>=0;i--){
  printf("%d \n", path[i] );
}

  return 0;
}
