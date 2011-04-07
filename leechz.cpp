#include <string>

#include "con_pool.h"

int main(int argc, char **argv)
{

    Connections *pool = new Connections("localhost", 5000, 0, 5);
    //Connections *pool = new Connections("eu.news.astraweb.com", 119);
    //Usenet *conn = new Usenet("localhost", 5000);
    pool->join();

    /* main loop */

    delete pool;

    return 0;
}
