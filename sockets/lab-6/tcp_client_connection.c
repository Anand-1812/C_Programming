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

  if (connect(sockfd, (struct sockaddr*)&server, sizeof(server)) == -1) {
    perror("Connection failed");
    return 1;
  }
  printf("Connected to server.\n");

  while (1) {
    printf("You: ");
    fgets(msg, sizeof(msg), stdin);
    msg[strcspn(msg, "\n")] = '\0';

    send(sockfd, msg, strlen(msg), 0);
    if (strcmp(msg, "exit") == 0) {
      printf("Exiting client...\n");
      break;
    }

    int k = recv(sockfd, msg, sizeof(msg) - 1, 0);
    if (k <= 0) {
      printf("Server disconnected.\n");
      break;
    }
    msg[k] = '\0';
    printf("Server: %s\n", msg);

    if (strcmp(msg, "exit") == 0) {
      printf("Server ended chat. Closing client...\n");
      break;
    }
  }

  close(sockfd);
  return 0;
}
