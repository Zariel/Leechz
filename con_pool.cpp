/* Connection pool to manage our connections, check for updates and organise
 * downloads */


#include "con_pool.h"

Connections::Connections(char *host, int port, int ipv6, int count)
    :host(host), port(port), ipv6(ipv6), count(count), Thread()
{
    epfd = epoll_create(count);


    int i;
    for(i = 0; i < count; i++) {
        /* Not connected */
        Usenet *conn = new Usenet(host, port, ipv6);

        pool.push_back(conn);

        static struct epoll_event ev;
        ev.events = EPOLLIN | EPOLLPRI | EPOLLERR | EPOLLHUP;
        ev.data.fd = *(conn->get_socket());
    }
}

Connections::~Connections()
{
}

int Connections::exec()
{
    /* Poll all of the epoll sockets and release locks to download */
    while(1) {
        int nfds = epoll_wait(epfd, events,
            MAX_EPOLL_EVENTS_PER_RUN, EPOLL_RUN_TIMEOUT);

        /* TODO: Log this */
        if (nfds < 0) return 1);

        for(int i = 0; i < nfds; i++) {
            int fd = events[i].data.fd;
        }
    }

    return 0;
}

