//
// Created by chnvideo on 2016/4/2.
//

#ifndef RTMP_SERVER_ERROR_TYPE_HPP
#define RTMP_SERVER_ERROR_TYPE_HPP

#define ERROR_SUCCESS                         0
#define ERROR_INVALID_PARAMETER                 1
#define ERROR_CONNECTIONS_OVER_LIMITS           2
#define ERROR_RTMP_NOT_SUPPORT_VERSION          3
#define ERROR_KERNEL_STREAM_INIT                    4

/////////////////////////////////////////////////
// st errors
/////////////////////////////////////////////////
#define ERROR_ST_SET_ENENTSYS_FAILED        100
#define ERROR_ST_INIT_FAILED                    101
#define ERROR_ST_THREAD_CREATE_FAILED           102
#define ERROR_ST_ACCEPT_FAILED                      103
#define ERROR_ST_READ_FULLY                     104
#define ERROR_ST_WRITE_FAILED                       105

/////////////////////////////////////////////////
// system invoke errors
//////////////////////////////////////////////////
#define ERROR_SOCKET_CREATE_FAILED              200
#define ERROR_SOCKET_BIND_FAILED                201
#define ERROR_SOCKET_LISTEN_FAILED              202
#define ERROR_ST_NETFD_OPEN_SOCKET_FAILED      203


#endif //RTMP_SERVER_ERROR_TYPE_HPP
