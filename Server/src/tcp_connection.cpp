#include "../include/tcp_connection.h"

TCPConnection::pointer TCPConnection::Create(io_service& io)
{
    return pointer(new TCPConnection(io));
}

tcp::socket& TCPConnection::Socket()
{
    return _socket;
}

void TCPConnection::Start(MessageReceivedCallback callback)
{
    _callback = callback;
    Read();
}

void TCPConnection::Read()
{
    std::fill(_data, _data + max_size, 0);
    auto self(shared_from_this());
    _socket.async_read_some(
        buffer(_data, max_size),
        boost::bind(&TCPConnection::HandleRead, self,
                    placeholders::error,
                    placeholders::bytes_transferred));
}

void TCPConnection::Write(const std::string& msg)
{
    auto self(shared_from_this());
    _socket.async_write_some(
        buffer(msg),
        boost::bind(&TCPConnection::HandleWrite, self,
                    placeholders::error,
                    placeholders::bytes_transferred));
}

void TCPConnection::HandleRead(const boost::system::error_code& error, size_t bytes_transferred)
{
    if (!error && bytes_transferred > 0)
    {
        std::string msg(_data, bytes_transferred);
        _callback(msg);
        Read();
    }
    else if (error == boost::asio::error::eof)
    {
        std::cout << "Client disconnected." << std::endl;
    }
    else 
    {
        std::cout << "Read error: " << error.message() << std::endl;
    }
}

void TCPConnection::HandleWrite(const boost::system::error_code& error, size_t bytes_transferred)
{
    if (!error)
    {
        std::cout << "Sent: " << bytes_transferred << " bytes." << std::endl;
    }
    else 
    {
        std::cout << "Write error: " << error.message() << std::endl;
    }
}
