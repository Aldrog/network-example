#include <arpa/inet.h>	//Для типов socket, sockaddr_in, и для связанных с ними функций и констант
#include <unistd.h>	//Для операций read и write над потоками данных
#include <stdlib.h>	//Для exit
#include <iostream>	//Для std
#include <stdio.h>	//Для perror

//Максимальная длина принимаемой строки (может быть любой)
const int MAXLINE = 64;

//Выводит сообщение и завершает программу
int ExitWithError(char* e){
  perror(e);
  exit(2);
}

int main(int argc, char ** argv){
  if(argc < 2)
    ExitWithError((char*)"Missing IP-address");
  
  int sockfd,n;	//Дескриптор сокета и длина полученной строки
  char recvline[MAXLINE];	//Строка
  struct sockaddr_in servaddr;	//Информация о сервере
  //Открываем сокет, записываем дескриптор в sockfd
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0)
    ExitWithError((char*)"Error opening socket");
  //Задаём тип адреса - IPv4
  servaddr.sin_family = AF_INET;
  //Задаём порт
  servaddr.sin_port = htons(322);
  //Задаём IP-адрес
  inet_pton(AF_INET,argv[1],&servaddr.sin_addr);
  std::cout << "Connecting to " << argv[1] << '\n';
  //Подключаемся к серверу
  if(connect(sockfd, (sockaddr *) &servaddr, sizeof(servaddr)) < 0)
    ExitWithError((char*)"Error connecting");
  //Читаем из сокета в recvline
  while ( (n = read(sockfd, recvline, MAXLINE)) > 0) {
    //Выводим полученное сообщение на экран
    std::cout << recvline << '\n';
  }
  if(n < 0)
    ExitWithError((char*)"Error reading");
  return 0;
}