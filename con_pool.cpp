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
		ev.ptr = conn;

		epoll_ctl(epfd, EPOLL_CTL_ADD, *(conn->get_socket()), &ev);
    }
}

Connections::~Connections()
{
}

int Connections::exec()
{
	struct epoll_event *events;
	Usenet *conn;

    /* Poll all of the epoll sockets and release locks to download */
    while(1) {
        int nfds = epoll_wait(epfd, events,
            max_events, epoll_timeout);

        /* TODO: Log this */
        if (nfds < 0) return 1);

        for(int i = 0; i < nfds; i++) {
			conn = events[i].data.ptr;
        }
    }

    return 0;
}

