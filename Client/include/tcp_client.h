#pragma once

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <memory>

using namespace boost::asio;
using ip::tcp;

class TCPClient : public std::enable_shared_from_this<TCPClient>
{
public:
    using pointer = std::shared_ptr<TCPClient>;

    static pointer Create(io_service& io);
    void Connect(tcp::resolver::iterator enpointIter);
    void Write(const std::string& msg);
    void Read();

private:
    TCPClient(io_service& io) : _socket(io) {}
    void HandleConnect(const boost::system::error_code& error);
    void HandleWrite(const boost::system::error_code& error, size_t bytes_transferred);
    void HandleRead(const boost::system::error_code& error, size_t bytes_transferred);

    enum { max_size = 1024 };
    char _data[max_size];
    tcp::socket _socket;
};