#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string>

using namespace std;

int main(int argc, char ** argv){
  int listenfd,connfd;
  char buff[64] = "hello";
  struct sockaddr_in servaddr;
  listenfd = socket(AF_INET,SOCK_STREAM,0);
  if(listenfd < 0)
    perror("Error opening socket");
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(322);
  if(bind(listenfd, (sockaddr *) &servaddr, sizeof(servaddr)) < 0)
    perror("Error binding socket");
  if(listen(listenfd, 5) < 0)
    perror("Error setting socket to listen state");
  while (1) {
    connfd = accept(listenfd, (sockaddr *) NULL, (socklen_t *) NULL);
    if(connfd < 0)
      perror("Error accepting request");
    write(connfd, buff, 5);
    close(connfd);
  }
  return 0;
}