#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <limits.h>

#define Data char

typedef struct Stack{
  Data data;
  struct Stack *next;
} Stack;

void printstack(Stack *stack){
  Stack *tmp=NULL;
  tmp=stack;
  printf("-------\n");
  while (tmp!=NULL){
    printf("[%p][%d]-> [%p] \n",tmp, tmp->data , tmp->next);
    tmp=tmp->next;
  }
  printf("-------\n");
}

void push(Stack **stack, Data data){
  Stack *tmp=NULL;
  if ((tmp=malloc(sizeof(stack)))==NULL){
    exit(1);
  }
  tmp->data=data;

  if (stack==NULL){
    tmp->next=NULL;
  } else{
    tmp->next=*stack;
  }
  *stack=tmp;
}
Data pop(Stack **stack){
  Stack *tmp=NULL;
  if (stack==NULL){
    exit(1);
  }
  tmp=*stack;
  *stack=(*stack)->next;
  return tmp->data;
}

Data top(Stack *stack){
  return stack->data;
}

Stack *is_empty(Stack *stack){
  if (stack==NULL){
    return NULL;
  } else{
    return stack;
  }
}

void drop(Stack **stack){
  while ((*stack)->next != NULL) {
        pop(stack);
        *stack = (*stack)->next;
    }
  free(*stack);
	*stack = NULL;
}

int main(int argc, char * argv[]) {
  Stack *stack;
  Data ok;
  push(&stack,2);
  push(&stack,3);
  push(&stack,4);
  printstack(stack);
  printf("%p\n", is_empty(stack) );
  drop(&stack);
  printstack(stack);
  printf("%p\n", is_empty(stack) );
  
  // printf("%d\n", stack->data );
  // ok=pop(&stack);
  // ok=pop(&stack);
  //
  // ok=top(stack);
  // printf("%d\n",ok );
  // printstack(stack);

  return 0;
}
