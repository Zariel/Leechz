#ifndef USENET_H
#define USENET_H

#include <string>

#include "threadp.h"
#include "connection.h"

using namespace std;

class Article
{
private:
    int part;
    int size;
    string article;
    string file_name;

public:
    Article(string article, int size, int part, string file_name);
    ~Article();
};

class Usenet : public Thread
{
private:
    Article *article;

    Lock io_lock;

    char *host;
    int port;
    int ipv6;

    int io_buffer_len;
    Connection *socket;
    void init();

public:
    Usenet(char *host, int port, int ipv6 = 0);
    virtual ~Usenet();
    virtual int exec();
    virtual void buffer_io();
    int connect_err;

    Lock download_lock;
    Lock kill_lock;
    Lock *init_lock;

    int login(string name, string pw);
    void flush_io();
    int download(string article, int size, int part, string file_name);
    int _auth();
    int *get_socket();
};

#endif
