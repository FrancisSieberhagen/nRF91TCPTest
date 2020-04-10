#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h> 

#include <sys/wait.h>


void
sig_chld(int signo)
{
    pid_t   pid;
    int     stat;

    while ( (pid = waitpid(-1, &stat, WNOHANG)) > 0)
        printf("Child %d terminated\n", pid);
    return;
}

int main(void)
{
    struct sockaddr_in sa;
    struct sockaddr_in cli_addr;
    socklen_t fromlen;
    int childpid, bytes_sent;
    struct timeval tv;

    char buffer[1024];
    int recsize;

    char ip_client[INET_ADDRSTRLEN];
    fromlen = sizeof cli_addr;

    int SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (SocketFD == -1) {
      perror("cannot create socket");
      exit(EXIT_FAILURE);
    }
  
    memset(&sa, 0, sizeof sa);
  
    sa.sin_family = AF_INET;
    sa.sin_port = htons(42501);
    sa.sin_addr.s_addr = htonl(INADDR_ANY);

  
    if (bind(SocketFD,(struct sockaddr *)&sa, sizeof sa) == -1) {
      perror("bind failed");
      close(SocketFD);
      exit(EXIT_FAILURE);
    }

    if (listen(SocketFD, 10) == -1) {
      perror("listen failed");
      close(SocketFD);
      exit(EXIT_FAILURE);
    }

    signal(SIGCHLD, sig_chld);  /* must call waitpid() */

  
    for (;;) {
      int ConnectFD = accept(SocketFD, (struct sockaddr *)&cli_addr, &fromlen);

  
      if (0 > ConnectFD) {
        perror("accept failed");
        close(SocketFD);
        exit(EXIT_FAILURE);
      }

      // set TIMEOUT
      tv.tv_sec = 20;
      tv.tv_usec = 0;
      setsockopt(ConnectFD, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);

      /* Create child process */
      if ( (childpid = fork()) == 0) {
        close(SocketFD);

        inet_ntop(AF_INET, &cli_addr.sin_addr, ip_client, INET_ADDRSTRLEN);
        printf("Connect from %s:%d on child %d\n",ip_client, ntohs(sa.sin_port), getpid());

        for (;;) {

          recsize = recv(ConnectFD, buffer, sizeof buffer, 0);
          if (recsize <= 0) {
            break;
          }

          buffer[recsize] = '\0';
          printf("Received packet Data %d : [%s] on child %d\n",recsize, buffer, getpid());


          bytes_sent = send(ConnectFD, buffer, strlen(buffer), 0);
          if (bytes_sent <= 0) {
            printf("Error sending packet: %s\n", strerror(errno));
            break;
          }
        }

        close(ConnectFD);
        close(SocketFD);
        exit(0);
      } else {

        close(ConnectFD);
        continue;
      }
    }

    close(SocketFD);
    return EXIT_SUCCESS;  
}
