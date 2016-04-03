//
// Created by chnvideo on 2016/4/2.
//

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "rtmp_server.hpp"
#include "error_type.hpp"
#include "logger.hpp"
#include "utility.hpp"

#define LISTENQ_SIZE_DEFAULT        128
#define MAX_CONNECTIONS             1000

RtmpServer::RtmpServer(int p)
{
    port = p;
    // max client to serve
    max_connections = MAX_CONNECTIONS;
}

RtmpServer::~RtmpServer()
{
}

int RtmpServer::initialize()
{
    int ret = ERROR_SUCCESS;

    if ((ret = st_set_eventsys(ST_EVENTSYS_ALT)) != ERROR_SUCCESS) {
        ret = ERROR_ST_SET_ENENTSYS_FAILED;
        log_error("st_set_eventsys failed, ret=%d", ret);
        return ret;
    }

    if ((ret = st_init()) != ERROR_SUCCESS) {
        ret = ERROR_ST_INIT_FAILED;
        log_error("st init failed, ret=%d", ret);
        return ret;
    }

    return ret;
}

int RtmpServer::listen()
{
    int ret = ERROR_SUCCESS;

    int skt;
    if ((skt = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        ret = ERROR_SOCKET_CREATE_FAILED;
        log_error("create socket failed, ret=%d", ret);
        return ret;
    }

    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = inet_addr("0.0.0.0");

    if (bind(skt, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        ret = ERROR_SOCKET_BIND_FAILED;
        log_error("sockt bind failed, ret=%d", ret);
        return ret;
    }

    if (::listen(skt, LISTENQ_SIZE_DEFAULT) < 0) {
        ret = ERROR_SOCKET_LISTEN_FAILED;
        log_error("listen failed, ret=%d", ret);
        return ret;
    }

    if ((server_nfd = st_netfd_open_socket(skt)) == NULL) {
        ret = ERROR_ST_NETFD_OPEN_SOCKET_FAILED;
        log_error("st_netfd_open_socket failed, ret=%d", ret);
        return ret;
    }

    return ret;
}

int RtmpServer::cycle()
{
    int ret = ERROR_SUCCESS;
    st_netfd_t cli_nfd;

    // accept client
    while(true) {
        if ((ret = accept_client(cli_nfd)) != ERROR_SUCCESS) {
            return ret;
        }
    }

    return ret;
}

int RtmpServer::accept_client(st_netfd_t cli_nfd)
{
    int ret = ERROR_SUCCESS;

    struct sockaddr from;
    int fromlen;

    if ((cli_nfd = st_accept(server_nfd, (struct sockaddr*)&from, &fromlen, ST_UTIME_NO_TIMEOUT)) == NULL) {
        ret = ERROR_ST_ACCEPT_FAILED;
        log_error("st_accept failed, ret=%d", ret);
        return ret;
    }

    // check connection limitions
    if ((int)conns.size() > max_connections) {
        int fd = st_netfd_fileno(cli_nfd);
        ret = ERROR_CONNECTIONS_OVER_LIMITS;
        log_error("conns=%d exceed the max_conns=%d, drop the client: fd=%d. ret=%d", (int)conns.size(), max_connections, fd, ret);
        return ret;
    }

    // if not exceed the max_connections, create a connection
    RtmpClient* conn = new RtmpClient(cli_nfd);
    conns.push_back(conn);

    if ((ret = conn->start()) != ERROR_SUCCESS) {
        return ret;
    }

    return ret;
}
