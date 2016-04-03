//
// Created by chnvideo on 2016/4/2.
//

#ifndef RTMP_SERVER_RTMP_SERVER_HPP
#define RTMP_SERVER_RTMP_SERVER_HPP

#include <vector>
#include "st/st.h"
#include "st_thread.hpp"
#include "st_connection.hpp"

using namespace std;

/**
 * the server to serve the client, handle the client's
 * handshake, connection and so on.
 */
class RtmpServer : public IStThread
{
private:
    // the rtmp server listen port
    int port;
    // rtmp server socket
    st_netfd_t server_nfd;
    // the max connections of the rtmp serve
    int max_connections;
    // all connections
    std::vector<RtmpClient* > conns;
private:
    RtmpClient* cli;
public:
    RtmpServer(int p);
    virtual ~RtmpServer();
public:
    virtual int initialize();
    virtual int listen();
    virtual int cycle();
public:
    virtual int accept_client(st_netfd_t cli_nfd);
};

#endif //RTMP_SERVER_RTMP_SERVER_HPP
