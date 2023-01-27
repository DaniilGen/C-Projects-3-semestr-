#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <limits.h>
#include "Stack.h"

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
    return 0;
  }
  tmp=*stack;
  if ((*stack)->next!=NULL){
    *stack=(*stack)->next;
  }
  else{
    *stack=NULL;
  }
  return tmp->data;
}

Data top(Stack *stack){
  if (stack!=NULL){
    return stack->data;
  } else{
    return (-1);
  }
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
