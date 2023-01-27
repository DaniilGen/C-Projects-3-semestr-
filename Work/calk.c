#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <unistd.h>

typedef struct Node{
  char data;
  struct Node *next;
}L1;

void push(L1 **head, char data){
  L1 *tmp;
  if(((tmp)=malloc(sizeof(L1))) == NULL){
    perror("malloc: NULL");
    exit(1);
  }
  tmp->data=data;
  if(head == NULL) tmp->next = NULL;
  else tmp-> next = *head;
  *head=tmp;

  // printf("%x\n",(*head)->data);
}

char pop(L1 **head){
  L1 *tmp=NULL;
  if (head==NULL){
    return 0;
  }
  tmp=*head;
  if ((*head)->next!=NULL){
    *head=(*head)->next;
  }
  else{
    *head=NULL;
  }
  return tmp->data;
}

char top(L1 *head){
  L1 *tmp=NULL;
  char i;
  if(head==NULL) return 0;
  else{
  tmp=head;
  while(tmp->next!=NULL) tmp=tmp->next;
  i= tmp->data;
  tmp->next=NULL;
  return i;
}
}
L1 *is_empry(L1* stack){
  if (stack==NULL) return NULL;
  else{return stack;}
}
void drop(L1 **stack){
  while(*stack!=NULL){
    pop(stack);
    *stack=(*stack)->next;
  }
  free(*stack);
  *stack=NULL;
}
void pr(L1 *stack){
  L1 *tmp=NULL;
  int i=0;
    tmp=stack;
      printf("[%d] %d\n",tmp->data,i);
      printf("%p->%p\n",tmp,tmp->next );
    while(tmp->next!=NULL){
      printf("[%d] %d\n",tmp->data,i);
      printf("%p->%p\n",tmp,tmp->next );
      tmp=tmp->next;
      i++;
    }
    printf("\n");
  }

int main(int argc,char *argv[]){
  L1 *stack=NULL;
  int i=0;
  int num,l, lol;
  char tmp;
  if(argc!=2){printf("problem\n"); return 0;}
  while(argv[1][i]!='\0'){
    tmp=argv[1][i];
    num=argv[1][i]-'0';
    printf("char: %c\n",tmp);
    printf("num:%d\n",num );
    if(num>=0 && num<=9){
      push(&stack,num);
      printf("%d\n",num );
      pr(stack);

  }else{
    switch (tmp) {
    case '-':
    l=pop(&stack);
    push(&stack,pop(&stack)-l);
    printf("---\n");
    break;
    case '+':
    lol=pop(&stack)+pop(&stack);
    printf("%d\n", lol);
    push(&stack,lol);
    pr(stack);
    break;

    case '/':
    l=pop(&stack);
    push(&stack,pop(&stack)/l);
    break;

    case '*':
      push(&stack,pop(&stack)*pop(&stack));
      break;

  }
}
i++;
}
  printf("-----rez-----:\n");
  printf("%d\n", top(stack));
  // pr(stack);

  return 0;
}
