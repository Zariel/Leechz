#include <sys/socket.h>
#include <netdb.h>
#include <sys/select.h>

#include <string.h> /* memset */
#include <stdio.h>  /* snpritnf */
#include <unistd.h> /* close */
#include <stdlib.h> /* atoi */

#include <string>

#include "connection.h"


Connection::Connection(char *host, int port, int ipv6)
    :host(host), port(port), ipv6(ipv6)
{
}

Connection::~Connection()
{
    if(connected) {
        _send("QUIT");
    }

    shutdown(sockfd, SHUT_RDWR);
    close(sockfd);
}


int Connection::_connect()
{
    if(connected) {
        return 1;
    }

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
        return err;
    }

    sockfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);

    /* Attempt connect */
    if((err = connect(sockfd, servinfo->ai_addr, servinfo->ai_addrlen)) < 0) {
        printf("unable to connect\n");
        return err;
    }

    connected = 1;

    return 1;
}

int Connection::_recv()
{

    recv_lock.acquire();

    recv_buffer = (char*) malloc(RECV_SIZE);

    int err = recv(sockfd, recv_buffer, RECV_SIZE, 0);

    buffer_io();

    recv_lock.release();
}

int Connection::_send(string data)
{
    int err = 0;
    fd_set wr;
    struct timeval t;

    FD_ZERO(&wr);
    FD_SET(sockfd, &wr);

    t.tv_sec = 5;
    t.tv_usec = 0;

    /* Can we write to socket ? */
    err = select(sockfd + 1, NULL, &wr, NULL, &t);

    if(err <= 0) {
        printf("Timeout or error in select\n");
        return -1;
    }

    int len = data.size();
    if(data[len - 1] != 0xa && data[len - 2] != 0xd) {
        data += { 0xd, 0xa };
        len += 2;
    }

    printf("SEND: %s\n", data.c_str());
    /* CR-LF */

    err = write(sockfd, data.c_str(), len);

    if(err < 0) {
        return -2;
    }
}

int* Connection::get_socket()
{
    return &sockfd;
}
