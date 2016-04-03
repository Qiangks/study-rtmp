//
// Created by chnvideo on 2016/4/2.
//

#ifndef RTMP_SERVER_ST_CONNECT_HPP
#define RTMP_SERVER_ST_CONNECT_HPP

#include "st/st.h"
#include "st_thread.hpp"

class RtmpClient : public IStThread
{
public:
    st_netfd_t cli_nfd;
    StThreadManger* handler;
public:
    RtmpClient(st_netfd_t nfd);
    virtual ~RtmpClient();
public:
    virtual int start();
    virtual int cycle();

private:
    virtual int read(char** pbuf, ssize_t  size);
    virtual int write(char* buf, ssize_t  size);
    virtual int handshake();
    virtual int create_s0s1s2(char* c1, char** s0s1s2);
};

#endif //RTMP_SERVER_ST_CONNECT_HPP
