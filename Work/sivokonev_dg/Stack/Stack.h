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

void printstack(Stack *stack);
void push(Stack **stack, Data data);
Data pop(Stack **stack);
Data top(Stack *stack);
Stack *is_empty(Stack *stack);
void drop(Stack **stack);
