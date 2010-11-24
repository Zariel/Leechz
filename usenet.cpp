
#include <sys/socket.h>
#include <netinet/in.h> /* sockaddr_in */
#include <arpa/inet.h>  /* inet_pton */

#include "Usenet.h"

Usenet::Usenet(char *host, int port)
{
    int err = 0;

    addr = new struct sockaddr_in;

    addr->sin_family = AF_INET;
    addr->sin_port = htons(port);

    if((err = inet_pton(AF_INET, host, &addr->sin_addr)) < 0) {
        /* err */
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    /* Attempt connect */
    if((err = connect(sockfd, (sockaddr *) addr, sizeof(*addr))) < 0) {
   }
}

Usenet::~Usenet()
{
    delete addr;
}

