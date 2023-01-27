#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <error.h>
#include <limits.h>
#include <strings.h>
#define SIZE 2048

typedef struct Node{
  int ch;
  struct Node * next;
} node;

void push(node **head, int ch){
  node *tmp=NULL;
  if ((tmp=malloc(sizeof(node)))==NULL){
    exit(1);
  }
  tmp->ch=ch;
  if (head==NULL)    tmp->next=NULL;
  else tmp->next=*head;
  *head=tmp;
}

int pop(node **head){
  int ch=(*head)->ch;
  *head=(*head)->next;
  return ch;

}

void vivod(node *head){
  node * tmp=head;
  while (tmp!=NULL){
    printf("%d \n", tmp->ch );
    tmp=tmp->next;
  }
  printf("\n" );
}

int main(int argc, char *argv[]) {
  int i,ch1,ch2, chet=0;
  node *head=NULL;
  char buf[SIZE];
  scanf("%s", buf );
  for (i=0; i<SIZE;i++){

    if (buf[i]!='\0'){
      if (buf[i]=='+'){
        chet=chet+1;
        ch1=pop(&head);
        ch2=pop(&head);
        push(&head,ch1+ch2);
        printf("Deistvie %d + \n", chet );
        vivod(head);
      } else{
        if (buf[i]=='-'){
          chet=chet+1;
          ch1=pop(&head);
          ch2=pop(&head);
          push(&head,ch2-ch1);
          printf("Deistvie %d - \n", chet );
          vivod(head);
        } else{
          if (buf[i]=='*'){
            chet=chet+1;
            ch1=pop(&head);
            ch2=pop(&head);
            push(&head,ch1*ch2);
            printf("Deistvie %d * \n", chet );
            vivod(head);
          } else{
            if (buf[i]=='/'){
              chet=chet+1;
              ch1=pop(&head);
              ch2=pop(&head);
              if (ch1==0){
                printf("DELENIE NA 0 \n");
                exit(0);
              }
              push(&head,ch2/ch1);
              printf("Deistvie %d / \n", chet );
              vivod(head);
            } else{
              push(&head,buf[i]-48);
            }
          }
        }
      }

    }
    else break;

  }
  printf("OTVET \n" );
  printf("%d\n", pop(&head) );

  return 0;
}
