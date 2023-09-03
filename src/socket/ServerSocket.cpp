#include <cerrno>
#include "ServerSocket.h"
using namespace pisco::socket;


ServerSocket::ServerSocket(const string &ip, int port)
{
    m_sockfd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_sockfd < 0)
    {
        printf("create server socket error: errno=%d", errno);  
    }
    set_non_blocking();
    set_recv_buffer(10 * 1024);
    set_send_buffer(10 * 1024 * 1024);
    set_linger(true, 0);
    set_keep_alive();
    set_reuse_addr();
    bind(ip, port);
    listen(1024);    
}