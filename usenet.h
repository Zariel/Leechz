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

    int io_buffer_len;
    Connection *socket;

public:
    Usenet(char *host, int port, int ipv6 = 0);
    ~Usenet();
    virtual int exec();
    virtual void buffer_io();

    Lock download_lock;

    int login(string name, string pw);
    void flush_io();
    int download(string article, int size, int part, string file_name);
    int _auth();
    int *get_socket();
};

#endif
