#include <pthread.h>

#include "threadp.h"

Thread::Thread()
{
    pthread_create(&thread, NULL, Thread::run, reinterpret_cast<void*>(this));
}

Thread::~Thread()
{
    //LOG("Exiting - tid = %u\n", thread);
    join();
}

int Thread::exit()
{
    int ret = 1;
    pthread_exit(&ret);
    return 0;
}

void *Thread::run(void *arg)
{
    reinterpret_cast<Thread*>(arg)->exec();
    return NULL;
}

int Thread::exec()
{
}

int Thread::join()
{
    void *ret;
    pthread_join(thread, &ret);

    return 0;
}

int Thread::cancel()
{
    pthread_cancel(thread);
}

pthread_t Thread::getID()
{
    return thread;
}

Lock::Lock()
{
    pthread_mutex_init(&_lock, NULL);
}

Lock::~Lock()
{
    release();
    pthread_mutex_destroy(&_lock);
}


int Lock::acquire(int block)
{
    int ret = 0;

    if(!block) {
        ret = pthread_mutex_trylock(&_lock);
    } else {
        ret = pthread_mutex_lock(&_lock);
    }

    locked = 1;

    return ret;
}

int Lock::release()
{
    if(locked) {
        pthread_mutex_unlock(&_lock);
    }

    locked = 0;

    return 0;
}
