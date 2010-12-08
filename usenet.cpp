#include <sys/socket.h>
#include <netdb.h>
#include <sys/select.h>

#include <string.h> /* memset */
#include <stdio.h>  /* snpritnf */
#include <unistd.h> /* close */
#include <stdlib.h> /* atoi */

#include <string>

#include "usenet.h"

Usenet::Usenet(char *host, int port, int ipv6)
    :host(host), port(port), ipv6(ipv6), Thread()
{
}

int Usenet::exec()
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
        return -1;
    }

    _recv();

    _send("HELP");
    _recv();

    connected = 1;

    return 0;
}

int parse(char *data, int *ret_code, string *ret_text)
{
    char buf[4];
    memcpy(buf, data, 3);
    buf[4] = '\0';

    ret_code = (int*) malloc(sizeof(int) * 3);
    *ret_code = atoi(buf);

    /* TODO:
     * Allocate ret_text
     * Make sure ends in CLRF ?
     */
    return 0;
}

int Usenet::_recv()
{
    /* need to find CR-LF to check for terminated string */
    int len = 0;
    char buf[512];
    int size = recv(sockfd, buf, 512, 0);

    /*
    int i = 1;
    while(buf[i - 1] != 0xd && buf[i - 1] != 0xa) {
        i++;
    }

    printf("0x%x 0x%x\n", buf[i - 1], buf[i]);
    printf("%d %d\n", i, size);
    */

    printf("%s%c\n", buf, 0);

    return size;
}

/** TLS:
 * connect
 * TLS?
 * STARTTLS
 * <- TLS STUFF ->
 * AUTH
 */

int Usenet::login(string name, string pw)
{
}

int Usenet::_auth()
{
}

/* ASSUMES DATA IS NOT CRLF TERMINATED */
int Usenet::_send(string data)
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

    printf("SEND: %s\n", data.c_str());
    /* CR-LF */
    data += { 0xd, 0xa };

    err = write(sockfd, data.c_str(), data.size());

    if(err < 0) {
        return -2;
    }
}

Usenet::~Usenet()
{
    if(connected) {
        _send("QUIT");
    }

    shutdown(sockfd, SHUT_RDWR);
    close(sockfd);
}

