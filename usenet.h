#ifndef USENET_H
#define USENET_H

#include "threadp.h"

using namespace std;

class Usenet : public Thread
{
private:
    typedef Thread super;

    int connected;
    int sockfd;

    char *host;
    int port;
    int ipv6;

    int _send(string data);
    int _recv();
    int _auth();

public:
    Usenet(char *host, int port, int ipv6 = 0);
    ~Usenet();

    int login(string name, string pw);
    virtual int exec();
};

#endif
