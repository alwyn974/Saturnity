/*
** EPITECH PROJECT, 2023
** Saturnity
** File description:
** server
*/

#include "../include/server.hpp"

using namespace saturnity;

void UdpServer::clearBuff(std::array<char, BUFF_SIZE> buffer)
{
    for (int i = BUFF_SIZE; i > 0; i--) { buffer[i] = '\0'; }
}

UdpServer::UdpServer(boost::asio::io_context& ioContext, int port) :
    _ioCtx(ioContext), _socket(ioContext, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port)), _port(port)
{
    // TODO: LAUNCH SERVER AND HANDLE RECEIVE / SENT
    //            std::string input;
    //            std::cin >> input;
    //            std::cout << input << std::endl;
    receive();
    //            if (_recvBuffer.size() > 0) {
    //                std::cout << "Received" << std::endl;
    //            }
    //            if (_sendBuffer.size() > 0) {
    //                std::cout << "Not empty" << std::endl;
    //            }
    //            clearBuff(_sendBuffer);
    // clearBuff(_recvBuffer);
    //            std::cout << "cleared" << std::endl;
}

UdpServer::~UdpServer()
{
    clearBuff(_sendBuffer);
    clearBuff(_recvBuffer);
    _socket.close();
}

void UdpServer::createSocket(int port)
{
    try {
        boost::asio::ip::udp::socket socket(_ioCtx, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port));
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

bool UdpServer::handshake()
{
    return 1;
}

void UdpServer::receive()
{
    //    std::cout << "receiving" << std::endl;
    _socket.async_receive_from(boost::asio::buffer(_recvBuffer), _remoteEndpoint ,boost::bind(&UdpServer::handleReceive, this, boost::asio::placeholders::error));
    // _ioCtx.run();
}

void UdpServer::handleReceive(const boost::system::error_code& error)
{
    if (error) {
        std::cerr << "ERROR RECEIVE ASYNC: " << error.message() << std::endl;
    } else {
        std::cout << "Handling: " << _recvBuffer.data() << "|" << std::endl;
        send("Allo");
    }
}

void UdpServer::send()
{
    // std::cout << "SENDING CLASS" << std::endl;
    std::string send_str = "Test";
    // std::copy(_sendBuffer.begin(), _sendBuffer.end(), send_str.data());

    _socket.async_send_to(boost::asio::buffer(send_str), _remoteEndpoint,
                          boost::bind(&UdpServer::handleSend, this, boost::asio::placeholders::error));
    //    _ioCtx.run();
}

void UdpServer::send(std::string input)
{
    // std::cout << "SENDING MESSAGE" << std::endl;
    std::copy(_sendBuffer.begin(), _sendBuffer.end(), input.data());
    _socket.async_send_to(boost::asio::buffer(_sendBuffer), _remoteEndpoint,
                          boost::bind(&UdpServer::handleSend, this, boost::asio::placeholders::error));
    //    _ioCtx.run();
}

void UdpServer::handleSend(const boost::system::error_code& error)
{
    if (error) {
        std::cerr << "ERROR SEND ASYNC: " << error.message() << std::endl;
    } else {
        std::cout << "ASYNC SENT" << std::endl;
        receive();
    }
}
