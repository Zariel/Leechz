#ifndef CONNECTION_H
#define CONNECTION_H

#include "threadp.h"

#define RECV_SIZE (4 * 1024)

using namespace std;

class Connection
{
public:
    Connection(char *host, int port, int ipv6);
    ~Connection();
    int *get_socket();
    int _recv();
    int _send(string data);
    int _connect();

private:
    char *host;
    int port;
    int ipv6;
    int connected;
    Lock recv_lock;
    int sockfd;
    char *recv_buffer;
    int recv_len;
};

#endif
