#include "../include/tcp_client.h"
#include <iostream>

int main()
{
    io_service io;

    std::cout << "Enter server port: ";
    std::string port;
    std::getline(std::cin, port);

    std::cout << "Enter your nickname: ";
    std::string nickname;
    std::getline(std::cin, nickname);

    tcp::resolver resolver(io);
    auto endpointIterator = resolver.resolve({"127.0.0.1", port});
    TCPClient::pointer client = TCPClient::Create(io);
    client->Connect(endpointIterator);
    std::thread io_thread([&io]() { io.run(); });
    std::string message;
    while (true) {
        std::getline(std::cin, message);

        if (!message.empty()) {
            client->Write(nickname + ": " + message);
        }

        message.clear();
    }

    io_thread.join();
    return 0;
}