/* Connection pool to manage our connections, check for updates and organise
 * downloads */


#include "con_pool.h"

    Connections::Connections(char *host, int port, int ipv6, int count)
:host(host), port(port), ipv6(ipv6), count(count), Thread()
{
    kill_lock = new Lock();
}

Connections::~Connections()
{
    int i;
    for(i = 0; i < count; i++) {
        delete 
}

void Connections::init()
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
        ev.data.ptr = conn;

        epoll_ctl(epfd, EPOLL_CTL_ADD, *(conn->get_socket()), &ev);
    }
}

int Connections::exec()
{
    init();

    struct epoll_event *events;
    Usenet *conn;

    /* Poll all of the epoll sockets and release locks to download */
    while(1) {
        printf("bitchin\n");
        if(!kill_lock->acquire(0)) {
            break;
        }

        int nfds = epoll_wait(epfd, events,
                              max_events, epoll_timeout);

        if (nfds < 0) return 1;

        for(int i = 0; i < nfds; i++) {
            conn = (Usenet*)events[i].data.ptr;
        }
    }

    return 0;
}
