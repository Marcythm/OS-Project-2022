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
    printf("ERROR opening socket");
    exit(1);
  }
  server = gethostbyname("127.0.0.1");
  if (server == NULL) {
    printf("ERROR, no such host");
    exit(0);
  }
  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
  serv_addr.sin_port = htons(portno);

  if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
    printf("ERROR connecting");
    exit(1);
  }
  printf("Please enter the message: \n");
  // DO NOT change this part if you are not familiar with Linux Network Programming
  ///////////////////////////////////////////////////////////////////



  ///////////////////////////////////////////////////////////////////
  return 0;
}