#include "../include/tcp_server.h"

void TCPServer::StartAccept()
{
    TCPConnection::pointer newConnection = TCPConnection::Create(_io);

     _acceptor.async_accept(newConnection->Socket(),
                            boost::bind(&TCPServer::HandleAccept, this, newConnection,
                                        placeholders::error));
}

void TCPServer::HandleAccept(TCPConnection::pointer newConnection, const boost::system::error_code &error)
{
    if (!error)
    {
        _connections.push_back(newConnection);
        newConnection->Start([this, newConnection](const std::string& msg)
        {
            Broadcast(msg, newConnection);
        });
    }

    StartAccept();
}

void TCPServer::Broadcast(const std::string& msg, TCPConnection::pointer sender)
{
    for(auto& connection : _connections)
    {
        if (connection != sender)
        {
            connection->Write(msg);
        }
    }
}