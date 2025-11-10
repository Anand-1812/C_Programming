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
  socklen_t ca_len;
  char msg[200];

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

  if (bind(sockfd, (struct sockaddr*)&sa, sizeof(sa)) == -1) {
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

  while (1) {
    int k = recv(newsockfd, msg, sizeof(msg) - 1, 0);
    if (k <= 0) {
      printf("Client disconnected.\n");
      break;
    }
    msg[k] = '\0';
    printf("Client: %s\n", msg);

    if (strcmp(msg, "exit") == 0) {
      printf("Client ended chat. Closing server...\n");
      break;
    }

    printf("You: ");
    fgets(msg, sizeof(msg), stdin);
    msg[strcspn(msg, "\n")] = '\0';

    send(newsockfd, msg, strlen(msg), 0);

    if (strcmp(msg, "exit") == 0) {
      printf("Server ended chat. Closing...\n");
      break;
    }
  }

  close(newsockfd);
  close(sockfd);
  return 0;
}
