#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {
  int sockfd, newsockfd;
  struct sockaddr_in sa, ca;
  char msg[200];
  socklen_t ca_len;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    perror("Socket creation failure");
    return 1;
  }
  printf("Socket created: %d\n", sockfd);

  sa.sin_family = AF_INET;
  sa.sin_port = htons(1206);
  sa.sin_addr.s_addr = INADDR_ANY;
  memset(&(sa.sin_zero), '\0', 8);

  int bindSocket = bind(sockfd, (struct sockaddr*)&sa, sizeof(sa));

  if (bindSocket == -1) {
    perror("Bind failure");
    return 1;
  }
  printf("Bind successful.\n");

  if (listen(sockfd, 5) == -1) {
    perror("Listen failure");
    return 1;
  }
  printf("Listening for clients...\n");

  ca_len = sizeof(ca);
  newsockfd = accept(sockfd, (struct sockaddr*)&ca, &ca_len);
  if (newsockfd == -1) {
    perror("Accept failure");
    return 1;
  }
  printf("Client connected.\n");

  close(newsockfd);
  close(sockfd);
  return 0;
}
