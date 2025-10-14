#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define IP "142.251.223.227"
#define PORT 80

int main() {
  int s;
  struct sockaddr_in sock;
  char buff[512];
  char* data;

  data = "HEAD /HTTP/1.0\n\n";

  s = socket(AF_INET, SOCK_STREAM, 0);
  if (s < 0) {
    printf("socket() error\n");
    return -1;
  }

  sock.sin_addr.s_addr = inet_addr(IP);
  sock.sin_port = htons(PORT);
  sock.sin_family = AF_INET;

  if (connect(s, (struct sockaddr *)&sock, sizeof(sock)) != 0) {
    printf("connect() error\n");
    close(s);
    return 1;
  }

  printf("Connected to %s : %d successfully!\n", IP, PORT);

  write(s, data, strlen(data));
  read(s, buff, 511);

  printf("\nData: %s\n", buff);

  close(s);
  return 0;
}
