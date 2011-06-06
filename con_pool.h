#ifndef CON_POOL_H
#define CON_POOL_H

#include <vector>
#include <sys/epoll.h>

#include "threadp.h"
#include "usenet.h"

using namespace std;

class Connections : public Thread
{
private:
    vector<Usenet*> pool;

    static const int max_events = 20;
    static const int epoll_timeout = 30;

    char *host;
    int port;
    int ipv6;
    int count;

    int epfd;
    void init();

public:
    Connections(char *host, int port, int ipv6, int count = 0);
    ~Connections();
    Lock *kill_lock;
    Lock *init_lock;

    virtual int exec();
};

#endif
