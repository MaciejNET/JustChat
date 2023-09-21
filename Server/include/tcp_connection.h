#pragma once

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/enable_shared_from_this.hpp>

using namespace boost::asio;
using ip::tcp;

class TCPConnection : public std::enable_shared_from_this<TCPConnection>
{
public:
    using pointer = std::shared_ptr<TCPConnection>;
    static pointer Create(io_service& io);
    tcp::socket& Socket();
    using MessageReceivedCallback = std::function<void(const std::string&)>;
    void Start(MessageReceivedCallback callback);
    void Read();
    void Write(const std::string& msg);

private:
    TCPConnection(io_service& io) : _socket(io) {}
    void HandleRead(const boost::system::error_code& error, size_t bytes_trasferred);
    void HandleWrite(const boost::system::error_code& error, size_t bytes_trasferred);
    enum {max_size = 1024};
    char _data[max_size];
    tcp::socket _socket;
    MessageReceivedCallback _callback;
};