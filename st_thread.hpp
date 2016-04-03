//
// Created by chnvideo on 2016/4/2.
//

#ifndef RTMP_SERVER_ST_THREAD_HPP
#define RTMP_SERVER_ST_THREAD_HPP

class IStThread
{
public:
    IStThread();
    virtual ~IStThread();
public:
    virtual int cycle() = 0;

};


class StThreadManger
{
private:
    IStThread* handler;
public:
    StThreadManger(IStThread* pst);
    virtual ~StThreadManger();
public:
    virtual int start();
    static void* thread_func(void*);
};

#endif //RTMP_SERVER_ST_THREAD_HPP
