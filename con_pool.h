#ifndef CON_POOL_H
#define CON_POOL_H

#include <vector>

#include "threadp.h"
#include "usenet.h"

using namespace std;

class Connections : public Thread
{
private:
    vector<Usenet*> pool;

    char *host;
    int port;
    int ipv6;
    int count;

public:
    Connections(char *host, int port, int ipv6, int count = 0);
    ~Connections();

    virtual int exec();
};

#endif
