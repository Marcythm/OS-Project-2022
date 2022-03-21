#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

int main(int argc, char *argv[]) {
  ///////////////////////////////////////////////////////////////////
  // DO NOT change this part if you are not familiar with Linux Network Programming
  int sockfd, portno, n;
  struct sockaddr_in serv_addr;
  struct hostent *server;
  char buffer[256];
  // the port number of server
  portno = 2050;
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    printf("ERROR opening socket\n");
    exit(1);
  }
  server = gethostbyname("127.0.0.1");
  if (server == NULL) {
    printf("ERROR, no such host\n");
    exit(0);
  }
  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
  serv_addr.sin_port = htons(portno);

  if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
    printf("ERROR connecting\n");
    exit(1);
  }
  printf("Please enter the message:\n");
  // DO NOT change this part if you are not familiar with Linux Network Programming
  ///////////////////////////////////////////////////////////////////

  while (1) {
    memset(buffer, 0, 256 * sizeof(char));
    fgets(buffer, 256, stdin);
    buffer[strlen(buffer) - 1] = '\0';
    // printf("message now: %s\n", buffer);

    n = write(sockfd, buffer, strlen(buffer));
    if (n < 0) {
      printf("ERROR writing to socket\n");
      exit(1);
    }

    if (strcmp(buffer, ":q") == 0) {
      printf("Client closing...\n");
      exit(0);
    }

    re_exec:
    n = read(sockfd, buffer, 255);
    if (n < 0) {
      printf("ERROR reading from socket\n");
      exit(1);
    }
    if (buffer[0] == 0 && buffer[1] == '1') {
      printf("From server: Please wait...\n");
      goto re_exec;
    }

    printf("From server: %s\n", buffer);
  }

  ///////////////////////////////////////////////////////////////////
  return 0;
}
