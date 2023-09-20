#include "../include/tcp_connection.h"

TCPConnection::pointer TCPConnection::Create(io_service& io)
{
    return pointer(new TCPConnection(io));
}

tcp::socket& TCPConnection::Socket()
{
    return _socket;
}

void TCPConnection::Start()
{
    Read();
}

void TCPConnection::Read()
{
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
    if (!error)
    {
        std::cout << "Receive message: " << std::string(_data, bytes_transferred) << std::endl;
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
