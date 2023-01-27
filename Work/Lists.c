#include <stdio.h>
#include <stdlib.h>
#include <time.h>


struct list{
  int data;
  struct list *next;
  struct list *prev;
}

struct list *add(list *lst, int a){
  struct list *temp, *p;
  temp= (struct list *) malloc (sizeof(list))
  p=lst->next;
  lst->next=temp;
  temp->data=a;
  temp->next=p;
  temp->prev=lst;
  if (p!=NULL){
    p->prev=temp;
  }
  return(temp);
}
struct list *del(list *lst){
  struct list *prev, *next;
  prev=lst->prev;
  next=lst->next;
  if (prev != NULL){
    prev->next=lst->next;
  }
  if (next != NULL){
    next->prev=lst->prev;
  }
  free(lst)
  return(prev);
}

void print(list *lst){
  struct list *p;
  p=lst;
  while (p!=NULL){
    printf("%d \n", p->data );
    p=p->next;
  }
}

int main(int argc, char * argv[]) {
  struct list *lst;
  lst = (struct list*)malloc(sizeof(struct list));
  lst->data=2;
  lst->next=NULL;
  lst->prev=NULL;
}
