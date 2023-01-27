#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <limits.h>


typedef struct Node{
  int data;
  struct Node *next;
} node;

node *add_head(node *head, int data){
  node *tmp=NULL;
  if ((tmp=malloc(sizeof(node)))==NULL){
    exit(1);
  }
  tmp->data=data;

  if (head==NULL){
    tmp->next=NULL;
  } else{
    tmp->next=head;
  }
  return(tmp);
}

node *add_head_node(node *head, node *add){
  node *tmp=NULL;
  tmp=add;
  tmp->data=add->data;
  // printf(" ok   %d \n", add->data );
  if (head==NULL){
    tmp->next=NULL;
  } else{
    tmp->next=head;
  }
  return(tmp);
}

node *del_head(node *head){
  node *tmp=NULL;
  if (head != NULL){
    tmp=head->next;
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
    printf("[%p][%d]-> [%p] \n",tmp, tmp->data , tmp->next);
    tmp=tmp->next;
  }
  printf("-------\n");
}

node *del(node *head, node *del){
  node *tmp1;
  tmp1=head;
  if (del==head){
    tmp1=head->next;
    return tmp1;
  }

  while (tmp1->next!=NULL && tmp1->next!=del){
    tmp1=tmp1->next;
  }
  if (tmp1){
    tmp1->next=tmp1->next->next;
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
  node *head =NULL;
  int len;
  head=add_head(head,20);
  head=add_head(head,10);
  head=add_head(head,340);
  head=add_head(head,230);
  head=add_head(head,1);
  printlist(head);

  head=sort_node(head);

  printlist(head);

  len= length(head);
  printf("len %d\n", len );
  printf("search 20 : %d\n", bin_search(head,len,20) );
  printf("search 21 : %d\n", bin_search(head,len,21) );
  return 0;
}

// node *sort_node(node *head){
//   node *tmp, *tmp1,*tmp2, *tmp3, *tmp4;
//   tmp=head;
//   while (head->next->next!=NULL){
//     tmp1=head->next;
//     tmp2=head->next->next;
//     // printf("head: [%p][%d]-> [%p] \n",head, head->data , head->next);
//     // printf("tmp1: [%p][%d]-> [%p] \n",tmp1, tmp1->data , tmp1->next);
//     // printf("tmp2: [%p][%d]-> [%p] \n",tmp2, tmp2->data , tmp2->next);
//     // printf("okk\n");
//     while (tmp2!=NULL){
//       printf("head: [%p][%d]-> [%p] \n",head, head->data , head->next);
//       printf("tmp1: [%p][%d]-> [%p] \n",tmp1, tmp1->data , tmp1->next);
//       printf("tmp2: [%p][%d]-> [%p] \n",tmp2, tmp2->data , tmp2->next);
//       if (tmp1->data>tmp2->data){
//         // printf("%d %d \n",tmp1->data , tmp2->data);
//         // printf("okk\n");
//         // printlist(tmp);
//         // printf("okk\n");
//         // printf("[%p][%d]-> [%p] \n",head, head->data , head->next);
//         // printf("[%p][%d]-> [%p] \n",tmp1, tmp1->data , tmp1->next);
//         // printf("[%p][%d]-> [%p] \n",tmp2, tmp2->data , tmp2->next);
//         // tmp2=head->next;
//         if (tmp1->next==tmp2){
//           head->next=tmp2;
//           tmp1->next=tmp2->next;
//           tmp2->next=tmp1;
//         } else{
//           head->next=tmp2;
//           tmp3=tmp1->next;
//           tmp1->next=tmp2->next;
//           tmp2->next=tmp3;
//           tmp4->next=tmp1;
//         }
//         printf("okk\n");
//         printlist(tmp);
//         // exit(0);
//         // printf("okk\n");
//       }
//       tmp4=tmp2;
//       tmp2=tmp2->next;
//     }
//     // printf("[%p][%d]-> [%p] \n",head, head->data , head->next);
//     // printlist(tmp1);
//
//     head=head->next;
//   }
//   return tmp1;
//
// }
