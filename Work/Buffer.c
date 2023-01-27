#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <error.h>
#include <limits.h>
#include <strings.h>
#define BUFFER_SIZE 4096
#define IFLAGS O_RDONLY
#define OFLAGS O_WRONLY|O_CREAT
#define N 40

typedef struct Node{
  long int data;
  struct Node *next;
  struct Node *prev;
  char s[N];
} node;

void _write(const char *path, node *head){
  int fd;
  ssize_t res;
  if ((fd=open(path, OFLAGS, 6000))<0){
    perror("open out:");
    exit(1);
  }
  // printf("OK\n");
  while (head){
    // printf("OK\n");
    res=write(fd,head,sizeof(node));
    // printf("\0%s\n", head->s);
    head=head->next;
  }
  if (res<0){
    perror("write:");
    exit(1);
  }
  close (fd);
}

node *add_head(node *head, int data, char *s){
  node *tmp=NULL, *tmp1=NULL;
  int i;
  char buffer[BUFFER_SIZE];
  // char *p;
  if ((tmp=malloc(sizeof(node)))==NULL){
    exit(1);
  }
  if (head==NULL){
    tmp->data=data;
    tmp->next=NULL;
    tmp->prev=NULL;
    // p=;
    bcopy(s,tmp->s, N);
    return tmp;
  }
  head->prev=tmp;

  bcopy(s,tmp->s, N);
  tmp->data=data;
  tmp->prev=NULL;
  tmp->next=head;
  return(tmp);
}

node *add_head_node(node *head, node *add){
  node *tmp=NULL;
  // char *p;
  if ((tmp=malloc(sizeof(node)))==NULL){
    exit(1);
  }
  bcopy(add->s,tmp->s, N);
  tmp->data=add->data;
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

node *_read(const char *path, node *head){
  int fd,i;
  ssize_t rd;
  node *buffer=NULL;
  if ((buffer=malloc(sizeof(node)))==NULL){
    exit(1);
  }
  if ((fd=open(path, IFLAGS))<0){
    perror("open in:");
    exit(1);
  }
  while ((rd=read(fd, buffer, sizeof(node)))>0){
    // printf("%d\n", buffer->data);
    head=add_head_node(head,buffer);
    }
  if (rd<0){
    perror("read: ");
    exit(4);
  }
  close (fd);
  return head;
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
    printf("[%p] <-[%p][%d][%s]-> [%p] \n",tmp->prev, tmp, tmp->data ,tmp->s, tmp->next);
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



int main(int argc, char *argv[]) {
  node *head=NULL;
  if (argc<3){
    fprintf(stderr, "cp filein fileout\n" );
    exit(1);
  }
  // head=add_head(head, 10, "okkefdfs");
  // head=add_head(head, 20, "ad3ksdffs");
  // head=add_head(head, 30, "dsf233sdfdfs");
  //
  // _write(argv[2], head);

  head=_read(argv[1],head);

  printlist(head);

  return 0;
}
