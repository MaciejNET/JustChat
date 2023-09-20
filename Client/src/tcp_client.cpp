#include "../include/tcp_client.h"

TCPClient::pointer TCPClient::Create(io_service& io)
{
    return pointer(new TCPClient(io));
}

void TCPClient::Connect(tcp::resolver::iterator endpointIter)
{
    auto self(shared_from_this());
    async_connect(_socket, endpointIter,
                  boost::bind(&TCPClient::HandleConnect, self,
                              placeholders::error));
}

void TCPClient::Write(const std::string& msg)
{
    auto self(shared_from_this());
        _socket.async_write_some(
        buffer(msg),
        boost::bind(&TCPClient::HandleWrite, self,
                    placeholders::error,
                    placeholders::bytes_transferred));
}

void TCPClient::Read()
{
    auto self(shared_from_this());
    _socket.async_read_some(
        buffer(_data, max_size),
        boost::bind(&TCPClient::HandleRead, self,
                    placeholders::error,
                    placeholders::bytes_transferred));
}

void TCPClient::HandleConnect(const boost::system::error_code& error)
{
    if (!error)
    {
        std::cout << "Connected to server." << std::endl;
        Read();
    }
    else
    {
        std::cerr << "Connect error: " << error.message() << std::endl;
    }
}

void TCPClient::HandleWrite(const boost::system::error_code& error, size_t bytes_transferred)
{
    if(error)
    {
        std::cerr << "Write error: " << error.message() << std::endl;
    }
}

void TCPClient::HandleRead(const boost::system::error_code& error, size_t bytes_transferred)
{
    if (!error)
    {
        std::cout << "Received message: " << std::string(_data, bytes_transferred) << std::endl;
        Read();
    }
    else if (error == boost::asio::error::eof)
    {
        std::cout << "Client disconnected." << std::endl;
    }
    else
    {
        std::cerr << "Read error: " << error.message() << std::endl;
    }
}
