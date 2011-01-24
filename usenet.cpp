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
        return -1;
    }

    sockfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);

    /* Attempt connect */
    if((err = connect(sockfd, servinfo->ai_addr, servinfo->ai_addrlen)) < 0) {
        printf("unable to connect\n");
        return -1;
    }

    char *buf;
    _recv(&buf);

    _send("HELP");
    _recv(&buf);
    if(buf != NULL) {
        printf("%s\n", buf);
    }

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

int Usenet::_recv(char **buf)
{
    int chunk_size = 1024;
    /* need to find CR-LF to check for terminated string */
    int len = 0;

    /* Read each buf into buffer then create buf at the end */
    char *buffer[10];
    int lengths[10];

    int i = 0;
    int size;

    while(i < 10) {
        buffer[i] = (char*) malloc(sizeof(char) * chunk_size);
        char *p = buffer[i];
        size = recv(sockfd, p, chunk_size, 0);

        lengths[i] = size;
        len += size;

        if(p[size - 1] == 0xa &&
           p[size - 2] == 0xd &&
           p[size - 3] == 0x2e &&
           p[size - 4] == 0xa &&
           p[size - 5] == 0xd) {
            /* muli length */
            len -= 5;
            lengths[i] -= 5;
            break;
        } else if(p[size - 1] == 0xa &&
                 p[size - 2] == 0xd) {
            /* get rid of crlf */
            lengths[i] -= 2;
            len -= 2;
            break;
        } else {
            return -1;
        }

        i++;
    }

    /*
    *buf = (char*) malloc(sizeof(char) * len);
    int offset = 0;
    int length = 0;
    for(i = 0; i < 10; i++) {
        char *p = buffer[i];
        while(*p) {
            **buf++ = *p++;
        }
    }
    */



    /*
    int i = 1;
    while(i < 512 && (*buf)[i] != 0xd && (*buf)[i - 1] != 0xa) {
        i++;
    }

    (*buf)[size] = '\0';
    */

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

Usenet::~Usenet()
{
    if(connected) {
        _send("QUIT");
    }

    shutdown(sockfd, SHUT_RDWR);
    close(sockfd);
}

