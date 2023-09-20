#include "../include/tcp_server.h"

int main()
{
    io_service io;
    TCPServer server(io, 8080);
    io.run();
    return 0;
}