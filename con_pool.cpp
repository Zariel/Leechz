/* Connection pool to manage our connections, check for updates and organise
 * downloads */


#include "con_pool.h"

    Connections::Connections(char *host, int port, int ipv6, int count)
:host(host), port(port), ipv6(ipv6), count(count), Thread()
{
    kill_lock = new Lock();
    init_lock = new Lock();

    init_lock->acquire();
    kill_lock->acquire();
}

Connections::~Connections()
{
    delete kill_lock;
    delete init_lock;
}

void Connections::init()
{
    Usenet *conn;
    epfd = epoll_create(count);

    /* Initialize worker threads in parrallell */
    int i;
    for(i = 0; i < count; i++) {
        conn = new Usenet(host, port, ipv6);

        pool.push_back(conn);
    }

    for(i = 0; i < count; i++) {
        conn = pool[i];
        /* Not connected */
        conn->init_lock->acquire();
        conn->init_lock->release();

        static struct epoll_event ev;
        ev.events = EPOLLIN | EPOLLPRI | EPOLLERR | EPOLLHUP;
        ev.data.fd = *(conn->get_socket());
        ev.data.ptr = conn;

        epoll_ctl(epfd, EPOLL_CTL_ADD, *(conn->get_socket()), &ev);
    }

    init_lock->release();
}

int Connections::exec()
{
    init();

    struct epoll_event *events;
    Usenet *conn;

    /* Poll all of the epoll sockets and release locks to download */
    while(1) {
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

    int i;
    for(i = 0; i < count; i++) {
        Usenet *conn = pool[i];
        //conn->kill_lock->release();

        int ret = conn->join();
        printf("%d\n", ret);
        delete conn;
    }


    return 0;
}
