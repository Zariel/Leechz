#include <pthread.h>

#include "threadp.h"

Thread::Thread()
{
    pthread_create(&thread, NULL, Thread::run, reinterpret_cast<void*>(this));
    id = pthread_self();
}

Thread::~Thread()
{
    exit();
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

int Thread::getID()
{
    return id;
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
