#include <sys/socket.h>
#include <netdb.h>
#include <sys/select.h>

#include <string.h> /* memset */
#include <stdio.h>  /* snpritnf */
#include <unistd.h> /* close */
#include <stdlib.h> /* atoi */

#include <string>

#include "usenet.h"
/* Should make socket its own thread instead of this class so we can kill it
 * nicely.
 */
Usenet::Usenet(char *host, int port, int ipv6)
    :host(host), port(port), ipv6(ipv6)
{
    init_lock = new Lock();
    init_lock->acquire();

    Thread();
}

Usenet::~Usenet()
{
    buffer_io();
    flush_io();

    delete &kill_lock;
    delete &socket;
}

void Usenet::init()
{
    printf("[0x%x] Usenet thread id = %u\n", this, getID());

    socket = new Connection(host, port, ipv6);
    connect_err = socket->_connect();

    download_lock = new Lock();
    kill_lock = new Lock();

    init_lock->release();
}

int Usenet::exec()
{
    init();

    while(1) {
        /*
        if(!kill_lock->acquire(0)) {
            break;
        }
        */

        download_lock->acquire();
        socket->_recv();
    }

    return 0;
}

int parse(char *data, int *ret_code, string *ret_text)
{
    char buf[4];
    memcpy(buf, data, 3);
    buf[4] = '\0';

    ret_code = (int*) malloc(sizeof(int) * 3);
    *ret_code = atoi(buf);

    /* TODO:
     * Allocate ret_text
     * Make sure ends in CLRF ?
     */
    return 0;
}

/*
 * The event watcher notifies that there is something to download and releases
 * the lock so we can fetch
 */

/** TLS:
 * connect
 * TLS?
 * STARTTLS
 * <- TLS STUFF ->
 * AUTH
 */

int Usenet::login(string name, string pw)
{
}

int Usenet::_auth()
{
}

int Usenet::download(string article, int size, int part, string file_name)
{

}

void Usenet::flush_io()
{
}

void Usenet::buffer_io()
{
}

int *Usenet::get_socket()
{
    return socket->get_socket();
}

