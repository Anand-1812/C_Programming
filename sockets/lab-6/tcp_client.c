#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {
  int sockfd;
  struct sockaddr_in server;
  char msg[200];

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    perror("Socket creation failed");
    return 1;
  }

  server.sin_family = AF_INET;
  server.sin_port = htons(1206);
  server.sin_addr.s_addr = inet_addr("127.0.0.1");
  memset(&(server.sin_zero), '\0', 8);

  int connectSocket = connect(sockfd, (struct sockaddr*)&server, sizeof(server));

  if (connectSocket == -1) {
    perror("Connection failed");
    return 1;
  }
  printf("Connected to server.\n");

  close(sockfd);
  return 0;
}
