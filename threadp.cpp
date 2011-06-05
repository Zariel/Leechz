#include <pthread.h>

#include "threadp.h"

Thread::Thread()
{
    pthread_create(&_id, NULL, Thread::run, reinterpret_cast<void*>(this));
}

Thread::~Thread()
{
    int ret = 0;
    pthread_exit(&ret);
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
    pthread_join(_id, &ret);

    return 0;
}

Lock::Lock()
{
    pthread_mutex_init(&_lock, NULL);
}

Lock::~Lock()
{
    pthread_mutex_destroy(&this->_lock);
}


int Lock::acquire(int block)
{
    int ret = 0;
    if(!block) {
        ret = pthread_mutex_trylock(&this->_lock);
    } else {
        ret = pthread_mutex_lock(&this->_lock);
    }

    return ret;
}

int Lock::release()
{
    pthread_mutex_unlock(&this->_lock);

    return 0;
}
