#include <arpa/inet.h>	//Для типов socket, sockaddr_in, и для связанных с ними функций и констант
#include <unistd.h>	//Для операций read и write над потоками данных
#include <stdlib.h>	//Для exit
#include <stdio.h>	//Для perror
#include <string.h>	//Для strlen

//Максимальная длина отправляемой строки (может быть любой)
const int MAXLINE = 64;

//Выводит сообщение и завершает программу
int ExitWithError(char* e){
  perror(e);
  exit(2);
}

int main(int argc, char ** argv){
  if(argc < 2)
    ExitWithError((char*)"Missing message");
  if(strlen(argv[1]) > MAXLINE)
    ExitWithError((char*)"Message is too long");
  
  int listenfd,connfd;	//Дескрипторы сокетов прослушивания и подключения
  char* msg = argv[1];	//Сообщение для отправки
  struct sockaddr_in servaddr;	//Информация о сервере
  //Открываем сокет и записываем дескриптор в listenfd
  listenfd = socket(AF_INET, SOCK_STREAM, 0);
  if(listenfd < 0)
    ExitWithError((char*)"Error opening socket");
  //Задаём тип адреса - IPv4
  servaddr.sin_family = AF_INET;
  //Задаём адрес (0.0.0.0/0.0.0.0)
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  //Задаём порт
  servaddr.sin_port = htons(322);
  //Связываем сокет с адресом servaddr
  if(bind(listenfd, (sockaddr *) &servaddr, sizeof(servaddr)) < 0)
    ExitWithError((char*)"Error binding socket");
  //Устанавливаем сокет в режим прослушивания (5 - максимальное количество клиентов)
  if(listen(listenfd, 5) < 0)
    ExitWithError((char*)"Error setting socket to listen state");
  while (1) {
    //При подключении клиента создаём сокет, дескриптор которого записываем в connfd
    connfd = accept(listenfd, (sockaddr *) NULL, (socklen_t *) NULL);
    if(connfd < 0)
      ExitWithError((char*)"Error accepting request");
    //Пишем в сокет сообщение
    write(connfd, msg, strlen(msg));
    //Закрываем сокет
    close(connfd);
  }
  return 0;
}