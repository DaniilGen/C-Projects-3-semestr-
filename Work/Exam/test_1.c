#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <signal.h>
#include <poll.h>

typedef struct Node {
  unsigned int k;
  struct Node *next;
} type_L;

type_L *add_head(type_L *head, unsigned int k){
  type_L *tmp=NULL;
  if ((tmp=malloc(sizeof(type_L)))==NULL){
    exit(1);
  }
  tmp->k=k;

  if (head==NULL){
    tmp->next=NULL;
  } else{
    tmp->next=head;
  }
  return(tmp);
}

void print(type_L *head){
  type_L *tmp=head;
  while (tmp!=NULL){
    printf("%u [%p] \n", tmp->k, tmp);
    tmp=tmp->next;
  }
}

unsigned long int amean(type_L *L){
  long int sum=0;
  int kol=0;
  type_L *tmp=L;
  if (L==NULL){
    // return -1; // ??? ф-ия unsigned возвращает значения >=0
    return 0;
  }
  while(tmp!=NULL){
    sum+=tmp->k;
    kol++;
    tmp=tmp->next;
  }
  return sum/kol;
}
int main(){
  type_L *head=NULL;
  printf("%u \n",amean(head) );
  head=add_head(head,24);
  head=add_head(head,31);
  head=add_head(head,423);
  printf("%u \n",amean(head) );

  // print(head);
}
