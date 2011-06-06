#ifndef THREAD_P
#define THREAD_P

#include <pthread.h>

class Thread
{
private:
    pthread_t thread;
    static void *run(void *arg);

public:
    Thread();
    virtual ~Thread();

    virtual int exec();
    int join();
    int exit();
    int cancel();
    pthread_t getID();
};

static int l_id = 0;

class Lock
{
private:
    pthread_mutex_t _lock;
    int locked;
    int id;

public:
    Lock();
    ~Lock();

    int acquire(int block = 1);
    int release();
};

#endif
