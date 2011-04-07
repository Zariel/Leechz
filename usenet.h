#ifndef USENET_H
#define USENET_H

#include <string>

#include "threadp.h"

#define RECV_SIZE (4 * 1024)

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
    typedef Thread super;

    int connected;
    int sockfd;

    char *host;
    int port;
    int ipv6;

    char *recv_buffer;

    Lock recv_lock;

    int _send(string data);
    int _recv();
    int _auth();

    Article *article;

public:
    Usenet(char *host, int port, int ipv6 = 0);
    ~Usenet();
    virtual int exec();

    Lock download_lock;

    int _connect();
    int login(string name, string pw);
    void flush_io();
    int download(string article, int size, int part, string file_name);
    int* get_socket();
};

#endif
