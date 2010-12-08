#include <pthread.h>

#include "threadp.h"

Thread::Thread()
{
    locked = 0;

    pthread_mutex_init(&_lock, NULL);
    pthread_create(&_id, NULL, Thread::run, reinterpret_cast<void*>(this));
}

Thread::~Thread()
{
    pthread_mutex_destroy(&this->_lock);
    int ret;
    pthread_exit(&ret);
}

void Thread::acquire(int block)
{
    if(!block) {
        pthread_mutex_trylock(&this->_lock);
    } else {
        pthread_mutex_lock(&this->_lock);
    }
}

int Thread::release()
{
    pthread_mutex_unlock(&this->_lock);

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
    int *ret;
    pthread_join(_id, NULL);

    return 0;
}
