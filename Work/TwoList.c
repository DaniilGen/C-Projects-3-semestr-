#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <limits.h>

typedef struct Node{
  int data;
  struct Node *next;
  struct Node *prev;
} node;

node *add_head(node *head, int data){
  node *tmp=NULL, *tmp1=NULL;
  if ((tmp=malloc(sizeof(node)))==NULL){
    exit(1);
  }
  if (head==NULL){
    tmp->data=data;
    tmp->next=NULL;
    tmp->prev=NULL;
    // printf("%p\n", tmp);
    return tmp;
  }
  head->prev=tmp;

  tmp->data=data;
  tmp->prev=NULL;
  tmp->next=head;
  return(tmp);
}

node *add_head_node(node *head, node *add){
  node *tmp=NULL;
  tmp=add;
  tmp->data=add->data;
  // printf(" ok   %d \n", add->data );
  if (head==NULL){
    tmp->next=NULL;
    tmp->prev=NULL;
  } else{
    tmp->next=head;
    tmp->prev=NULL;
    head->prev=tmp;
  }
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

node *add_tail(node *head, int data){
  node *tmp=NULL, *tmp2=NULL;
  if ((tmp=malloc(sizeof(node)))==NULL){
    exit(1);
  }
  tmp2=head;
  tmp->data=data;
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
  // free(head->next);
  head->next=NULL;
  return tmp;
}
void printlist(node *head){
  node *tmp=NULL;
  tmp=head;
  printf("-------\n");
  while (tmp!=NULL){
    printf("[%p] <-[%p][%d]-> [%p] \n",tmp->prev, tmp, tmp->data , tmp->next);
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

node *sort_node(node *head){
  node *tmp, *tmp1,*tmp2, *tmp3, *tmp4;
  int mindata;
  tmp=head;
  while (head->next!=NULL){
    tmp1=head;
    mindata=INT_MAX;
    // printf("%d \n", head->data );
    while (tmp1!=NULL){
      if (tmp1->data<mindata){
          mindata=tmp1->data;
          tmp2=tmp1;
        }
      tmp1=tmp1->next;
    }
    // printf("%d \n", tmp2->data );
    if (tmp2==head){
      head=head->next;
      tmp=del(tmp,tmp2);
      tmp=add_head_node(tmp,tmp2);
    } else{
      tmp=del(tmp,tmp2);
      tmp=add_head_node(tmp,tmp2);
    }
    // printlist(tmp);

  }
  if (tmp2->data<head->data){
    tmp1=head;
    tmp1->data=head->data;
    tmp=del_tail(tmp);
    tmp=add_head_node(tmp,tmp1);
  }
  return tmp;

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

int bin_search(node *head, int length, int data){
  int mid, i=0;
  node *tmp;
  tmp=head;
  while (i!=length/2){
    i++;
    tmp=tmp->next;
  }
  mid = tmp->data;
  if (mid==data){
    return 1;
  }
  if (head->data<=mid){
      return 0;
    }
  if (mid<data){
    bin_search(head, length/2, data);
  } else{
    bin_search(tmp, length-length/2, data);
  }
}

int main(int argc, char * argv[]) {
  node *head=NULL;
  int len;
  head=add_head(head,900);
  head=add_head(head,12);
  head=add_head(head,52);
  head=add_head(head,20);
  head=add_head(head,2);

  printlist(head);


    head=sort_node(head);

    printlist(head);

    len= length(head);
    printf("len %d\n", len );
    printf("search 52 : %d\n", bin_search(head,len,52) );
    printf("search 120 : %d\n", bin_search(head,len,120) );

  return 0;
}
