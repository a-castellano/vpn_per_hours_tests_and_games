// ServerPointer.cpp
// Álvaro Castellano Vela - 25/04/2016

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "ServerPointer.h"

ServerPointer::ServerPointer(const std::string &server, const int port)
    : server(server), port(port) {}

bool ServerPointer::point(const std::string &subdomain, const std::string &ip) {
  int sockfd, n;
  struct sockaddr_in serv_addr;
  struct hostent *server;

  char buffer[256];
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
    std::cout<<"ERROR opening socket"<<std::endl;
  server = gethostbyname(this->server);
  if (server == NULL) {
    fprintf(stderr, "ERROR, no such host\n");
    exit(0);
  }
  bzero((char *)&serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr,
        server->h_length);
  serv_addr.sin_port = htons(portno);
  if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    error("ERROR connecting");
  printf("Please enter the message: ");
  bzero(buffer, 256);
  fgets(buffer, 255, stdin);
  n = write(sockfd, buffer, strlen(buffer));
  if (n < 0)
    error("ERROR writing to socket");
  bzero(buffer, 256);
  n = read(sockfd, buffer, 255);
  if (n < 0)
                                                                                                                                                                                                                                                                                                                                                                         error("ERROR reading
																																																			 from socket");
																																											    printf("%s\n",buffer);
																																													    close(sockfd);
}
