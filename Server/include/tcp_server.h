#pragma once

#include <iostream>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <memory>
#include "../include/tcp_connection.h"

using namespace boost::asio;
using ip::tcp;

class TCPServer
{
public:
    TCPServer(io_service& io, int port) : _io(io), _acceptor(io, tcp::endpoint(tcp::v4(), port)) { StartAccept(); }

private:
    void StartAccept();
    void HandleAccept(TCPConnection::pointer newConnection, const boost::system::error_code& error);
    io_service& _io;
    tcp::acceptor _acceptor;
};