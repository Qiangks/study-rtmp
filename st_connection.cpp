//
// Created by chnvideo on 2016/4/2.
//

#include <string.h>
#include "st_connection.hpp"
#include "logger.hpp"
#include "error_type.hpp"
#include "st/st.h"
#include "utility.hpp"
#include "srs_kernel_buff.hpp"


RtmpClient::RtmpClient(st_netfd_t nfd)
{
    handler = new StThreadManger(this);
    cli_nfd = nfd;
}

RtmpClient::~RtmpClient()
{
    delete handler;
}

int RtmpClient::start()
{
    int ret = ERROR_SUCCESS;

    if ((ret = handler->start()) != ERROR_SUCCESS) {
        return ret;
    }

    return ret;
}

int RtmpClient::cycle()
{
    int ret = ERROR_SUCCESS;

    // handshake
    if ((ret = handshake()) != ERROR_SUCCESS) {
        return ret;
    }

    return ret;
}

int RtmpClient::read(char** pbuf, ssize_t  size)
{
    int ret = ERROR_SUCCESS;

    ssize_t nread;
    if ((nread = st_read_fully(cli_nfd, *pbuf, size, ST_UTIME_NO_TIMEOUT)) != size) {
        ret = ERROR_ST_READ_FULLY;
        log_error("read %d less than size=%d, ret=%d", nread, size, ret);
        return ret;
    }

    return ret;
}

int RtmpClient::write(char* buf, ssize_t  size)
{
    int ret = ERROR_SUCCESS;

    ssize_t nwrite;
    if ((nwrite = st_write(cli_nfd, buf, size, ST_UTIME_NO_TIMEOUT)) != size) {
        ret = ERROR_ST_WRITE_FAILED;
        log_error("write %d less than size=%d, ret=%d", nwrite, size, ret);
        return ret;
    }

    return ret;
}

int RtmpClient::handshake()
{
    int ret = ERROR_SUCCESS;

    char* c0c1= new char[1537];
    AutoFree(char, c0c1);
    if ((ret = read(&c0c1, 1537)) != ERROR_SUCCESS) {
        return ret;
    }

    if (c0c1[0] != 0x03) {
        ret = ERROR_RTMP_NOT_SUPPORT_VERSION;
        log_error("handshake not support c0 %x, ret=%d");
        return ret;
    }

    char* s0s1s2 = new char[3073];
    AutoFree(char, s0s1s2);
    if ((ret = create_s0s1s2(c0c1+1, &s0s1s2)) != ERROR_SUCCESS) {
        return ret;
    }

    if ((ret = write(s0s1s2, 3073)) != ERROR_SUCCESS) {
        return ret;
    }

    log_trace("handshake success!");
    char* c2 = new char[1536];
    AutoFree(char, c2);
    if ((ret = read(&c2, sizeof(c2))) != ERROR_SUCCESS) {
        return ret;
    }

    return ret;
}

int RtmpClient::create_s0s1s2(char *c1, char **s0s1s2)
{
    int ret = ERROR_SUCCESS;

    srs_random_generate(*s0s1s2, 3073);

    SrsBuffer stream;

    if ((ret =  stream.initialize(*s0s1s2, 9))) {
        return ret;
    }
    stream.write_1bytes(0x03);
    stream.write_4bytes((int32_t)::time(NULL));

    if (c1) {
        // s1 time2 copy from c1
        stream.write_bytes(c1, 4);
        // if c1 specified, copy c1 to s2.
        memcpy(*s0s1s2 + 1537, c1, 1536);
    }

    return ret;
}
