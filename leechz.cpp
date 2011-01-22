#include <string>

#include "usenet.h"

int main(int argc, char **argv)
{
    Usenet *conn = new Usenet("eu.news.astraweb.com", 119);
    //Usenet *conn = new Usenet("localhost", 5000);
    printf("%d\n", conn->join());

    /* main loop */

    delete conn;

    return 0;
}
