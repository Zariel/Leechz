#ifndef THREAD_P
#define THREAD_P

class Thread
{
private:
    pthread_t _id;
    static void *run(void *arg);

public:
    Thread();
    ~Thread();

    virtual int exec();
    int join();
};

class Lock
{
private:
    pthread_mutex_t _lock;
    int locked;

public:
    Lock();
    ~Lock();

    int acquire(int block);
    int release();
};

#endif
