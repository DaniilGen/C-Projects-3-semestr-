#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
   int sock, length;
   pid_t pid;
   struct sockaddr_in server;
   int msgsock;
   char buf[1024], command1[1024]="hello",command2[1024]="bye";
   int rval;
   const int enable = 1;

   sock = socket(AF_INET, SOCK_STREAM, 0);
   if (sock == -1) {
      perror("opening stream socket");
      exit(1);
   }

   server.sin_family = AF_INET;
   server.sin_addr.s_addr = htonl(INADDR_ANY);
   if(argc == 2) server.sin_port = htons(atoi(argv[1]));
   else server.sin_port = 0;

   if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
    perror("setsockopt(SO_REUSEADDR) failed");

   if (bind(sock, (struct sockaddr *) &server, sizeof server)  == -1) {
      perror("binding stream socket");
      exit(1);
   }

   length = sizeof server;
   if (getsockname(sock,(struct sockaddr *) &server, &length) == -1) {
      perror("getting socket name");
      exit(1);
   }
   printf("Socket port %d\n", ntohs(server.sin_port));

   if (listen(sock, 5) == -1) {
      perror("listen");
      exit(1);
   }

   while(1){
      if ((msgsock = accept(sock,(struct sockaddr *) 0,(int *) 0)) == -1)
         perror("accept");
      else {
        if((pid=fork()) < 0 ) {perror("fork");exit(1);}
        if (pid == 0) {
          do {
             close(sock);
             memset(buf, 0, sizeof buf);
             if ((rval = recv(msgsock, buf, 1024, 0)) == -1) perror("reading stream message");
             dprintf(0,"%d recieved %d\n",getpid(),rval);
             if (rval == 0)
                printf("Connection finished %d\n",getpid());
             else {
                write(1,buf,rval);
                printf("%s\n",buf );
                int flag1=1,flag2=1;
                for(int i=0;i<strlen(command1);i++){
                    if (buf[i]!=command1[i]) flag1=0;
                }
                for(int i=0;i<strlen(command2);i++){
                    if (buf[i]!=command2[i]) flag2=0;
                }

                // printf("1) %c %c %c %c %c\n", buf[1],buf[2],buf[3], buf[4],buf[5] );
                // printf("%d :  %d\n",flag, kol);
                // char otvet1[3]
                if (flag1) write(msgsock,")) hello ! \n",13);
                if (flag2) write(msgsock,")) bye ! \n",11);
 //               send(msgsock,buf,rval,0);
                printf("%d\n", strncmp(buf,command1,sizeof command1));
                // if (strcmp(buf,command1)==0){
                  // printf("pl\n" );
                  // write(msgsock,command1,rval);
                // }
                // write(msgsock,buf,rval);
             }
          } while (rval > 0);
          close(msgsock);
          exit(3);
       }
       printf("child pid %d on socket %d\n",pid,msgsock);
       close(msgsock);
     }
   }
   exit(0);
}
