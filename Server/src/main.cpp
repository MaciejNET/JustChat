#include "../include/tcp_server.h"

int main()
{
    io_service io;
    std::cout << "Enter server port: ";
    std::string port;
    std::getline(std::cin, port);
    TCPServer server(io, std::stoi(port));
    io.run();
    return 0;
}