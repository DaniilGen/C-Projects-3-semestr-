#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <limits.h>
#include "Stack.h"


int main(int argc, char * argv[]) {
  Stack *stack;
  int number,tmp;
  Data symbol;
  while ((symbol=getc(stdin))!=EOF){
    number=symbol-'0';
    if (number>=0 && number<=9){
      push(&stack,number);
    }else{
      switch (symbol) {
        case '*':
        push(&stack,pop(&stack)*pop(&stack));
        break;

        case '/':
        tmp=pop(&stack);
        push(&stack,pop(&stack)/tmp);
        break;

        case '+':
        push(&stack,pop(&stack)+pop(&stack));
        break;

        case '-':
        tmp=pop(&stack);
        push(&stack,pop(&stack)-tmp);
        break;

        case '\n':
        printf("%d\n", top(stack) );
          exit(1);
          break;

        default:
          printf("ERROR\n" );
      }
    }

  }

  return 0;
}
