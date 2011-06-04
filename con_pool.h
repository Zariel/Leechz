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

	const int max_events = 20;
	const int timeout = -1;


    char *host;
    int port;
    int ipv6;
    int count;

    int epfd;

public:
    Connections(char *host, int port, int ipv6, int count = 0);
    ~Connections();

    virtual int exec();
};

#endif
