#ifndef THREAD_P
#define THREAD_P

class Thread
{
private:
    pthread_t _id;
    pthread_mutex_t _lock;
    int locked;
    static void *run(void *arg);

public:
    Thread();
    ~Thread();

    void acquire(int block);
    int release();
    virtual int exec();

};

#endif
