#ifndef USENET_H
#define USENET_H

using namespace std;

class Usenet
{
private:
    int connected;
    int sockfd;

    int _send(string data);
    int _recv();
    int _auth();

public:
    Usenet(char *host, int port, int ipv6 = 0);
    ~Usenet();

    int login(string name, string pw);
};

#endif
