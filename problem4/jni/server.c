#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
void *serve(void *newsockfd);

pthread_mutex_t mutexcnt = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int threadcounter = 0;

int main(int argc, char *argv[]) {
  /////////////////////////////////////////////////////////////////
  // DO NOT change this part if you are not familiar with Linux Network Programming
  int sockfd, newsockfd, portno, clilen, n;
  char buffer[256];
  struct sockaddr_in serv_addr, cli_addr;
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    printf("ERROR opening socket \n");
    exit(1);
  }
  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  // the port number (>2000 generally) of server is randomly assigned
  portno = 2050;
  serv_addr.sin_port = htons(portno);
  // the ip address of server
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
    printf ("Error on binding\n");
    exit(1);
  }
  listen(sockfd, 5);
  clilen = sizeof(cli_addr);
  printf("Server initiating... \n");
  // DO NOT change this part if you are not familiar with Linux Network Programming
  ////////////////////////////////////////////////////////////////////

  while (1) {
    pthread_t thread;
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if (newsockfd < 0) {
      printf("ERROR on accept\n");
      exit(1);
    }

    pthread_create(&thread, NULL, serve, &newsockfd);
  }

  ////////////////////////////////////////////////////////////////////
  return 0;
}

char encrypt_c(const char c) {
  if ('a' <= c && c <= 'z')
    return (c + 3 > 'z') ? (c - 23) : (c + 3);
  else if ('A' <= c && c <= 'Z')
    return (c + 3 > 'Z') ? (c - 23) : (c + 3);
  else
    return c;
}

void *serve(void *sockfd) {
  int newsockfd = (int)(*((int*)sockfd));
  ////////////////////////////////////////////////////////////////////
  int n, i;
  char buffer[256];

  pthread_mutex_lock(&mutexcnt);
  if (threadcounter == 2) {
    pthread_mutex_unlock(&mutexcnt);
    write(newsockfd, "\0""1", 3); // inform the client to wait
    pthread_mutex_lock(&mutex); // wait for the control
    pthread_mutex_lock(&mutexcnt);
  } else if (threadcounter == 1)
    pthread_mutex_lock(&mutex);
  threadcounter++;
  pthread_mutex_unlock(&mutexcnt);

  while (1) {
    memset(buffer, 0, 256 * sizeof(char));
    n = read(newsockfd, buffer, 255);
    if (n < 0) {
      printf("ERROR reading from socket\n");
      exit(1);
    }

    printf("Receiving message: %s\n", buffer);

    if (strcmp(buffer, ":q") == 0) {
      printf("Server thread closing...\n");
      pthread_mutex_lock(&mutexcnt);
      threadcounter--;
      if (threadcounter == 1)
        pthread_mutex_unlock(&mutex);
      pthread_mutex_unlock(&mutexcnt);
      pthread_exit(0);
    }

    for (i = 0; i < n; i++)
      buffer[i] = encrypt_c(buffer[i]);
    n = write(newsockfd, buffer, n);
    if (n < 0) {
      printf("ERROR writing to socket\n");
      exit(1);
    }
  }

  ////////////////////////////////////////////////////////////////////
}
