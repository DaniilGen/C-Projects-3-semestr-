#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <unistd.h>

typedef struct Node{
  int data;
  struct Node *next;
  char c;
} node;

node *add_head(node *head, int data){
  node *tmp=NULL;
  if ( (tmp=malloc(sizeof(node))) == NULL) {
    perror("malloc: ");
    exit(1);
  }
  tmp->data = data;
  if (head == NULL){
    tmp->next=NULL;
  } else{
    tmp->next=head;
  }
  return(tmp);
}

node *add_tail(node *head, int data){
  node *tmp=NULL, *kok=NULL;
  kok=head;
  if ( (tmp=malloc(sizeof(node))) == NULL) {
    perror("malloc: ");
    exit(1);
  }
  tmp->data = data;
  while (head->next!=NULL){
    head=head->next;
  }
  head->next=tmp;
  return(kok);

}

node *del_head(node *head){
  node *tmp=NULL;
  if(head != NULL){
    tmp=head->next;
    free(head);
  }
  return tmp;
}

node *del_tail(node *head){
  node *tmp=NULL,*kok=head;
  tmp=head;
 while (kok->next != NULL){
    head=head->next;
    kok=head->next;
  }
  free(head->next);
  head->next=NULL;
  return tmp;
}
void printlist(node *head){
  node *tmp=NULL;
  tmp=head;
  while (tmp!=NULL){
    printf("[%p][%d]-> [%p] \n",tmp, tmp->data , tmp->next);
    tmp=tmp->next;
  }
}

int main(int argc, char *argv[]){
  node *head = NULL;
  node *tmp = NULL;
  head=add_head(head,10);
  head=add_head(head,20);
  head=add_head(head,30);
  head=add_tail(head,40);
  head=add_tail(head,45);
  head=del_tail(head);
  head=del_tail(head);
  head=del_head(head);
  printlist(head);
  return 0;
}
