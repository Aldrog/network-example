#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <string>

using namespace std;

int main(int argc, char ** argv){
  int sockfd,n;
  char recvline[64];
  struct sockaddr_in servaddr;
  sockfd = socket(AF_INET,SOCK_STREAM,0);
  if(sockfd < 0)
    perror("Error opening socket");
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(322);
  inet_pton(AF_INET,argv[1],&servaddr.sin_addr);
  cout << "Connecting to " << argv[1] << '\n';
  if(connect(sockfd, (sockaddr *) &servaddr, sizeof(servaddr)) < 0)
    perror("Error connecting");
  while ( (n = read(sockfd,recvline,64)) > 0) {
    if(n < 0)
      perror("Error reading");
    cout << recvline << '\n';
  }
  return 0;
}