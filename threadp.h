#ifndef THREAD_P
#define THREAD_P

#include <pthread.h>

class Thread
{
private:
    pthread_t thread;
    static void *run(void *arg);
    int id;

public:
    Thread();
    virtual ~Thread();

    virtual int exec();
    int join();
    int exit();
    int cancel();
    int getID();
};

class Lock
{
private:
    pthread_mutex_t _lock;
    int locked;

public:
    Lock();
    ~Lock();

    int acquire(int block = 1);
    int release();
};

#endif
