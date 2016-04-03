#include <iostream>
#include <stdlib.h>
#include "logger.hpp"
#include "error_type.hpp"
#include "rtmp_server.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    int ret = ERROR_SUCCESS;

    if (argc != 2) {
        printf(
            "Usage:\n"
                    "       %s <listen_port>\n"
            "For example:\n"
                    "       %s 1990\n",
                argv[0], argv[0]);
        ret = ERROR_INVALID_PARAMETER;
        return ret;
    }

    int port = atoi(argv[1]);
    RtmpServer* server = new RtmpServer(port);

    if ((ret = server->initialize()) != ERROR_SUCCESS) {
        return ret;
    }

    if ((ret = server->listen()) != ERROR_SUCCESS) {
        return ret;
    }

    if ((ret = server->cycle()) != ERROR_SUCCESS) {
        return ret;
    }

    delete server;
    return ret;
}