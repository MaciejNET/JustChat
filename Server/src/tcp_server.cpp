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
        newConnection->Start();
    }

    StartAccept();
}