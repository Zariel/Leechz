#include <sys/socket.h>
#include <netdb.h>
#include <sys/select.h>

#include <string.h> /* memset */
#include <stdio.h>  /* snpritnf */
#include <unistd.h> /* close */
#include <string>

#include "usenet.h"

Usenet::Usenet(char *host, int port, int ipv6)
{
    int err = 0;
    struct addrinfo hints;
    struct addrinfo *servinfo;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = (ipv6 ? AF_INET6 : AF_INET);
    hints.ai_socktype = SOCK_STREAM;

    char _port[10];
    snprintf(_port, 10, "%d", port);

    if((err = getaddrinfo(host, _port, &hints, &servinfo)) < 0) {
        printf("getaddrinfo failed\n");
    }

    sockfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);

    /* Attempt connect */
    if((err = connect(sockfd, servinfo->ai_addr, servinfo->ai_addrlen)) < 0) {
        printf("unable to connect\n");
    }

    connected = 1;
}

int Usenet::_send(std::string data)
{
    /* Can we write to socket ? */
    int err = 0;
    fd_set wr;
    struct timeval t;

    FD_ZERO(&wr);
    FD_SET(sockfd, &wr);

    t.tv_sec = 5;
    t.tv_usec = 0;

    err = select(sockfd + 1, NULL, &wr, NULL, &t);

    if(err <= 0) {
        printf("Timeout or error in select\n");
        return -1;
    }

    err = write(sockfd, data.c_str(), data.size());

    if(err < 0) {
        return -2;
    }
}

Usenet::~Usenet()
{
    _send("QUIT");
    shutdown(sockfd, SHUT_RDWR);
    close(sockfd);
}

