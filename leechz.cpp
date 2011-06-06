#include <string>

#include "con_pool.h"

int main(int argc, char **argv)
{

    Connections *pool = new Connections("localhost", 5000, 0, 2);
    //Connections *pool = new Connections("eu.news.astraweb.com", 119);
    //Usenet *conn = new Usenet("localhost", 5000);
    /* Let it init */
    pool->init_lock->acquire();
    pool->init_lock->release();

    pool->kill_lock->release();

    pool->join();

    /* main loop */

    delete pool;

    return 0;
}
