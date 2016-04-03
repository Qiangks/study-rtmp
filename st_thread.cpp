//
// Created by chnvideo on 2016/4/2.
//

#include "st_thread.hpp"
#include "error_type.hpp"
#include "st/st.h"

IStThread::IStThread()
{
}

IStThread::~IStThread()
{
}

StThreadManger::StThreadManger(IStThread *pst)
{
    handler = pst;
}

StThreadManger::~StThreadManger()
{
    delete handler;
}

int StThreadManger::start()
{
    // create the thread
    int ret = ERROR_SUCCESS;

    if (st_thread_create(thread_func, handler, 0, 0) == NULL) {
        ret = ERROR_ST_THREAD_CREATE_FAILED;

    }

    st_usleep(10);

    return ret;
}

void* StThreadManger::thread_func(void *arg)
{
    IStThread* obj = (IStThread*)arg;
    obj->cycle();

    // if cycle return, exit the thread
    st_thread_exit(NULL);

    return NULL;
}