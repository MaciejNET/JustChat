#include "../include/tcp_client.h"
#include <iostream>

int main()
{
    io_service io;
    tcp::resolver resolver(io);
    auto endpointIterator = resolver.resolve({"127.0.0.1", "8080"});
    TCPClient::pointer client = TCPClient::Create(io);
    client->Connect(endpointIterator);
    std::thread io_thread([&io]() { io.run(); });
    std::string message;
    while (true) {
        std::cout << "Enter message: ";
        std::getline(std::cin, message);

        if (!message.empty()) {
            client->Write(message);
        }

        message.clear();
    }

    io_thread.join();
    return 0;
}