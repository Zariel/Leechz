#include "usenet.h"

int main(int argc, char **argv)
{
    //Usenet *conn = new Usenet("eu.news.astraweb.com", 119, 0);
    Usenet *conn = new Usenet("localhost", 5000);

    delete conn;

    return 0;
}
