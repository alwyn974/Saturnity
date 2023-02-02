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
        for (int i = 1023; i > 0; i--) { buffer[i] = '\0'; }
}

UdpServer::UdpServer(int port) : _socket(_ioCtx, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port)), _port(port){
        // TODO: LAUNCH SERVER AND HANDLE RECEIVE / SENT
        while (1) {
//            std::string input;
//            std::cin >> input;
//            std::cout << input << std::endl;
            receive();
//            if (_recvBuffer.size() > 0) {
//                std::cout << "Received" << std::endl;
//            }
//            if (_sendBuffer.size() > 0) {
//                std::cout << "Not empty" << std::endl;
//                send();
//            }
            clearBuff(_sendBuffer);
            clearBuff(_recvBuffer);
//            std::cout << "cleared" << std::endl;

        }
}

UdpServer::~UdpServer() {
        clearBuff(_sendBuffer);
        clearBuff(_recvBuffer);
        _socket.close();
}

void UdpServer::createSocket(int port) {
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

void UdpServer::receive() {
//    std::cout << "receiving" << std::endl;
    _socket.async_receive_from(boost::asio::buffer(_recvBuffer), _remoteEndpoint, boost::bind(&UdpServer::handleReceive, this, boost::asio::placeholders::error, _recvBuffer));
    _ioCtx.run();
}

void UdpServer::handleReceive(const boost::system::error_code& error, std::array<char, BUFF_SIZE> recvBuffer) {
    if (error) {
        std::cerr << "ERROR ASYNC: " << error.message() << std::endl;
    } else {
        std::cout << "Handling" << std::endl;
        // TODO: How to print received buffer ;-;
//        std::cout << "HAVE:" << std::endl;
//        for (char c:recvBuffer) {
//                std::cout << c;
//        }
    }
}

void UdpServer::send() {
    _socket.async_send_to(boost::asio::buffer(_sendBuffer), _remoteEndpoint, boost::bind(&UdpServer::handleSend, this, boost::asio::placeholders::error, _sendBuffer));
    _ioCtx.run();
}

void UdpServer::handleSend(const boost::system::error_code& error, std::array<char, BUFF_SIZE> sendBuffer) {
    if (error) {
        std::cerr << "ERROR ASYNC: " << error.message() << std::endl;
    }
    std::cout << "ASYNC SENT: " << sendBuffer.begin() << " WITH LEN: " << sendBuffer.size() << std::endl;
}

