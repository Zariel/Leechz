#include <sys/socket.h>
#include <netdb.h>
#include <sys/select.h>

#include <string.h> /* memset */
#include <stdio.h>  /* snpritnf */
#include <unistd.h> /* close */
#include <stdlib.h> /* atoi */

#include <string>

#include "usenet.h"

Usenet::Usenet(char *host, int port, int ipv6)
    :Thread()
{
    socket = new Connection(host, port, ipv6);
    connect_err = socket->_connect();
}

Usenet::~Usenet()
{
    buffer_io();
    flush_io();

    delete socket;
}

int Usenet::exec()
{
    while(1) {
        download_lock.acquire();
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

