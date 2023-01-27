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


typedef struct Data{
  long int i;
  char s[24];
} data;


typedef struct Node{
  data Q;
  struct Node *next;
  struct Node *prev;
} L2;

data random_data(){
  data data;
  int j;
  data.i = rand() % 100;

  for (j = 0; j < 23; j++) {
      data.s[j] = (char) (rand() % 26 + 65);
  }
  data.s[23]='\0';
  return data;
}

void _write(const char *path, L2 *head){
  int fd;
  ssize_t res;
  data *buffer=NULL;
  if ((buffer=malloc(sizeof(data)))==NULL){
      exit(1);
    }
  if ((fd=open(path, OFLAGS, 6000))<0){
    perror("open out:");
    exit(1);
  }
  while (head){
    *buffer=head->Q;
    res=write(fd,buffer,sizeof(data));
    head=head->next;
  }
  if (res<0){
    perror("write:");
    exit(1);
  }
  close (fd);
}

L2 *add_head(L2 *head){
  L2 *tmp=NULL, *tmp1=NULL;
  data data=random_data();
  if ((tmp=malloc(sizeof(L2)))==NULL){
    exit(1);
  }
  if (head==NULL){
    tmp->Q=data;
    tmp->next=NULL;
    tmp->prev=NULL;
    return tmp;
  }
  head->prev=tmp;
  tmp->Q=data;
  tmp->prev=NULL;
  tmp->next=head;
  return(tmp);
}

L2 *add_head_data(L2 *head, data *add){
  L2 *tmp=NULL;
  if ((tmp=malloc(sizeof(L2)))==NULL){
    exit(1);
  }
  bcopy(add->s,tmp->Q.s, 24);
  tmp->Q.i=add->i;
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

L2 *add_head_node(L2 *head, L2 *add){
  L2 *tmp=NULL;
  if ((tmp=malloc(sizeof(L2)))==NULL){
    exit(1);
  }
  tmp->Q=add->Q;
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

L2 *_read(const char *path, L2 *head){
  int fd,i;
  ssize_t rd;
  data *buffer=NULL;
  if ((buffer=malloc(sizeof(data)))==NULL){
    exit(1);
  }
  if ((fd=open(path, IFLAGS))<0){
    perror("open in:");
    exit(1);
  }
  while ((rd=read(fd, buffer, sizeof(data)))>0){
    printf("%d %s\n", buffer->i,buffer->s);
    head=add_head_data(head,buffer);
    }
  if (rd<0){
    perror("read: ");
    exit(4);
  }
  close (fd);
  return head;
}

void printdata(data data){
  printf("%d %s \n",data.i,data.s );
}

void printlist(L2 *head){
  L2 *tmp=NULL;
  tmp=head;
  printf("-------\n");
  while (tmp!=NULL){
    printf("[%p] <-[[%p] %d %s]-> [%p] \n",tmp->prev,tmp, tmp->Q.i,tmp->Q.s,tmp->next);
    tmp=tmp->next;
  }
  printf("-------\n");
}

L2 *add_tail(L2 *head){
  L2 *tmp=NULL, *tmp2=NULL;
  data data= random_data();
  if ((tmp=malloc(sizeof(L2)))==NULL){
    exit(1);
  }
  tmp2=head;
  tmp->Q=data;
  while (head->next!=NULL){
      head=head->next;
  }
  head->next=tmp;
  tmp->prev=head;
  return(tmp2);
}

L2 *del_head(L2 *head){
  L2 *tmp=NULL;
  if (head != NULL){
    tmp=head->next;
    tmp->prev=NULL;
    free(head);
  }
  return tmp;
}

L2 *del_tail(L2 *head){
  L2 *tmp=NULL;
  tmp=head;
 while ((head->next)->next != NULL){
    head=head->next;
  }
  head->next=NULL;
  return tmp;
}

L2 *del_mid(L2 *head, L2 *del){
  L2 *tmp1;
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
L2 *find(L2 *head, data data){
  L2 *tmp1;
  tmp1=head;

  while (tmp1->next!=NULL && tmp1->Q.i!=data.i && tmp1->Q.s!=data.s){
    tmp1=tmp1->next;
  }

  return tmp1;
}

L2 *min (L2 *head){
  L2 *tmp1, *tmp2;
  tmp1=head;
  tmp2=head;

  while (tmp1->next!=NULL){
    if (tmp1->Q.i<tmp2->Q.i){
      tmp2=tmp1;
    }
    tmp1=tmp1->next;
  }

  return tmp2;
}
L2 *sort_node(L2 *head){
  L2 *tmp, *tmp1,*tmp2, *tmp3, *tmp4;
  int mindata;
  tmp=head;
  while (head->next!=NULL){
    tmp1=head;
    mindata=INT_MAX;
    while (tmp1!=NULL){
      if (tmp1->Q.i<mindata){
          mindata=tmp1->Q.i;
          tmp2=tmp1;
        }
      tmp1=tmp1->next;
    }
    if (tmp2==head){
      head=head->next;
      tmp=del_mid(tmp,tmp2);
      tmp=add_head_node(tmp,tmp2);
    } else{
      tmp=del_mid(tmp,tmp2);
      tmp=add_head_node(tmp,tmp2);
    }

  }
  if (tmp2->Q.i<head->Q.i){
    tmp1=head;
    tmp1->Q.i=head->Q.i;
    tmp=del_tail(tmp);
    tmp=add_head_node(tmp,tmp1);
  }
  return tmp;

}

int length(L2 *head){
  int kol=0;
  L2 *tmp=NULL;
  tmp=head;
  while (tmp!=NULL){
    kol++;
    tmp=tmp->next;
  }
  return kol;
}

int bin_search(L2 *head, int length, int data){
  int mid, i=0;
  L2 *tmp;
  tmp=head;
  while (i!=length/2){
    i++;
    tmp=tmp->next;
  }
  mid = tmp->Q.i;
  if (mid==data){
    return 1;
  }
  if (head->Q.i<=mid){
      return 0;
    }
  if (mid<data){
    bin_search(head, length/2, data);
  } else{
    bin_search(tmp, length-length/2, data);
  }
}

int main(int argc, char *argv[]) {
  L2 *head=NULL, *tmp;
  data data;
  // if (argc<3){
    // fprintf(stderr, "cp filein fileout\n" );
    // exit(1);
  // }

  head=add_head(head);
  head=add_head(head);
  // printlist(head);

  head=add_head(head);
  head=add_head(head);
  head=add_head(head);
  head=add_head(head);
  head=add_head(head);
  printlist(head);

  head=sort_node(head);
  printlist(head);

  // data=head->next->next->Q;

  printf("%d \n", length(head) );

  printf("search %d  : %d\n", head->next->next->next->Q.i, bin_search(head,length(head),head->next->next->next->Q.i) );
  printf("search %d  : %d\n", head->next->Q.i, bin_search(head,length(head),head->next->Q.i) );
  printf("search 100  : %d\n", bin_search(head,length(head),100) );
  // tmp=find(head,data);
  // tmp=min(head);
  // printf("%p %ld %s \n", tmp, tmp->Q.i, tmp->Q.s );

  // printlist(head);
  // head=add_tail(head);
  // printlist(head);
  // head=add_head(head);
  // printlist(head);
  //
  // head=del_tail(head);
  // printlist(head);


  // head=del_mid(head,head->next->next);




  // _write(argv[2], head);

  // head=_read(argv[1],head);

  printlist(head);

  return 0;
}
