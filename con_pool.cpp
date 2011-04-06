/* Connection pool to manage our connections, check for updates and organise
 * downloads */


#include "con_pool.h"

Connections::Connections(char *host, int port, int ipv6, int count)
    :host(host), port(port), ipv6(ipv6), count(count), Thread()
{
}

Connections::~Connections()
{
}

int Connections::exec()
{
    int i;
    for(i = 0; i < count; i++) {
        /* Not connected */
        Usenet *conn = new Usenet(host, port, ipv6);

        pool.push_back(conn);
    }

    return 0;
}

