#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
  int data;
  int weght;
  struct Node *next;
  struct Node *prev;
} node;

int graph_size( char *name){
FILE *input;
int d1,d2,f,n=0;

if ((input=fopen(name,"r"))==NULL) exit(2);
while (fscanf(input,"%d %d %d", &d1, &d2, &f)!= EOF){
if (d1>n) n=d1;
if (d2>n) n=d2;

}
fclose(input);
return n;
}

node *add_head(node *head, int hh ,int l){
  node *tmp=NULL;
  if((tmp=malloc(sizeof(node))) == NULL){
    perror("malloc: NULL");
    exit(2);
  }
  tmp->prev=NULL;
  tmp->data=hh;
  tmp->weght=l;
  if(head==NULL)tmp->next=NULL;
  else{
  tmp->next=head;
  head->prev=tmp;
}
  return tmp;
}

node *add_tail(node*head, int hh, int l){
  node *tmp=NULL;
  node *t=NULL;
  if((tmp=malloc(sizeof(node))) == NULL){
    perror("malloc: NULL");
    exit(3);

  }
  tmp->data=hh;
  tmp->weght=l;
  tmp->next=NULL;
  if(head==NULL) tmp->prev=NULL;
  else{
  t=head;
  while(t->next!=NULL) t=t->next;
  t->next=tmp;
  tmp->prev=t;
}


  return head;
}
void print_mas(int M, node * mas[M]){
  int i=0;
  for(i;i<M;i++){
    node *tmp=NULL;
    if(mas[i]==NULL){printf("00");}
    tmp=mas[i];
    printf("[%d]",tmp->data);
    tmp=tmp->next;
    while(tmp!=NULL){
    printf("--->[%d weght: %d]",tmp->data,tmp->weght);
    tmp=tmp->next;
  }
  printf("\n");
}
}
node *del_head(node *head){

  if(head->next==NULL){
    free(head);
    head=NULL;
  }
  if(head==NULL) return NULL;
  head=head->next;
  head->prev=NULL;
  // free(head->prev);

  return head;
}
void free_node(node *tmp){
  node *ss;
  ss=tmp;
  while(ss!=NULL){
    ss=del_head(ss);
  }
}
int length(node *list){
  node *tmp=NULL;
  int len=0;
  if(list==NULL) return 0;
  tmp=list;
  while (tmp!=NULL) {
    len++;
    tmp=tmp->next;
  }
  return len;
}
int end(int M,int m[M]){
  int i=0;
  int j=0;
  for(i;i<M;i++){
    if(m[i]==1000){
      j++;
    }
  }
  return j;
}

// void pass(int M,int i,int k,node *mas[M],int m[M]){
//   node *tmp=NULL;
//   int id[M];
//   int min_weght=1000;
//   int l;
//   for(l=0;l<M;l++){
//     id[l]=0;
//   }
//   id[i-1]=1;
//   tmp=mas[i-1];
//   m[i-1]=0;
//   for(l=0;l<M;l++){
//     if(l==(i-1)){
//       m[l]=0;
//     }
//     m[l]=min_weght;
//   }
//
// while(end(M,m)!=0){
//   node *tmp1=tmp;
//   while(tmp1!=NULL){
//     if(tmp1->weght<m[(tmp1->data)-1])
//     m[(tmp1->data)-1]=tmp1->weght;
//     tmp1=tmp1->next;
//   }
//   id[(tmp->data)-1]=1;
//   tmp=tmp->next;
//
// }
// }




int main(int argc, char * argv[]) {
  int M=graph_size(argv[1]);
  node * mas[M];
  int m[M];
  FILE *input;
  int d1,d2,weght;
  int i=1;


  while (i<=M) {
  node *tmp=NULL;
  tmp=add_head(tmp,i,0);
  if ((input=fopen(argv[1],"r"))==NULL) exit(2);
  while (fscanf(input,"%d %d %d", &d1, &d2, &weght)!= EOF){
    int t;
    if(d1==i){
    tmp=add_tail(tmp,d2,weght);
}
  }
  fclose(input);
  mas[i-1]=tmp;

  i++;

}
print_mas(M,mas);
i=2;
int j=5;

node *tmp=NULL;
  int id[M];
  int min_weght=1000;
  int l;
  for(l=0;l<M;l++){
    id[l]=0;
  }
  id[i-1]=1;
  tmp=mas[i-1];
  m[i-1]=0;
  for(l=0;l<M;l++){
    if(l==(i-1)){
      m[l]=0;
    }else{
    m[l]=min_weght;
  }}
  // for(l=0;l<M;l++){
  //   printf("%d!\n",m[l] );
  // }

while(end(M,m)!=0){
  node *tmp1=tmp;
  while(tmp1!=NULL){
    if(tmp1->weght<m[(tmp1->data)-1])
    m[(tmp1->data)-1]=tmp1->weght;
    tmp1=tmp1->next;

    }
    for(l=0;l<M;l++){
      printf("%d\n",m[l] );
  }
  id[(tmp->data)-1]=1;
  if(tmp->next!=NULL)
  tmp=tmp->next;

  if (end(M,m)==1){
    for(l=0;l<M;l++)
      printf("%d\n",m[l] );
      exit(0);
  }

}

// pass(M,2,5,mas,m);
// for(int l=0;l<M;l++){
//   printf("%d\n",m[l] );




  return 0;
}
