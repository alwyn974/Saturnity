/*
** EPITECH PROJECT, 2023
** Saturnity
** File description:
** server
*/

#include "../include/server.hpp"
#include "ByteBuffer.hpp"

using namespace saturnity;

std::list<std::string> split_str(size_t pos, std::string& s, std::string delimiter)
{
    std::string token;
    std::list<std::string> parsed;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        parsed.insert(parsed.cend(), token);
        //        std::cout << token << std::endl;
        s.erase(0, pos + delimiter.length());
    }
    return parsed;
}

void UdpServer::clearBuff(std::array<char, BUFF_SIZE> buffer)
{
    for (int i = BUFF_SIZE; i > 0; i--) { buffer[i] = '\0'; }
}

UdpServer::UdpServer(boost::asio::io_context& ioContext, int port) :
    _ioCtx(ioContext), _socket(ioContext, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port)), _port(port), _clientCount(0)
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
    //    _allEndpoint.clear();
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
    _socket.async_receive_from(boost::asio::buffer(_recvBuffer), _remoteEndpoint,
                               boost::bind(&UdpServer::handleReceive, this, boost::asio::placeholders::error));
}

void UdpServer::handleReceive(const boost::system::error_code& error)
{
    if (error) {
        std::cerr << "ERROR RECEIVE ASYNC: " << error.message() << std::endl;
    } else {
        std::string received = std::string(_recvBuffer.data());

        if ((received.compare(std::string("Hey")) && (!isInList(_remoteEndpoint)))) {
            //         TODO: CHECK DATA TO DETERMINE IF NEW
            addClient(_remoteEndpoint, _clientCount);
            broadcast(_remoteEndpoint, received);
        } else {
            std::cout << "Handling: " << _recvBuffer.data() << "|" << std::endl;
            broadcastAll(received);
        }
    }
}

void UdpServer::send(std::string& input)
{
    _socket.async_send_to(boost::asio::buffer(input), _remoteEndpoint, boost::bind(&UdpServer::handleSend, this, boost::asio::placeholders::error));
}

void UdpServer::send(boost::asio::ip::udp::endpoint remoteEndpoint, std::string& input)
{
    _socket.async_send_to(boost::asio::buffer(input), remoteEndpoint, boost::bind(&UdpServer::handleSend, this, boost::asio::placeholders::error));
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

void UdpServer::broadcast(boost::asio::ip::udp::endpoint sender, std::string& message)
{
    std::cout << "BROADCAST" << std::endl;
    for (const auto& [key, remote] : _clientList) {
        if (remote != sender)
            send(remote, message);
    }
    receive();
}

void UdpServer::broadcastAll(std::string& message)
{
    std::cout << "BROADCAST ALL" << std::endl;
    for (const auto& [key, remote] : _clientList) { send(remote, message); }
    receive();
}

bool UdpServer::isInList(const boost::asio::ip::udp::endpoint newEndpoint)
{
    for (const auto& item : _clientList) {
        if (item.second == newEndpoint) { return true; }
    }
    return false;
}

void UdpServer::addClient(const boost::asio::ip::udp::endpoint newEndpoint, int id)
{
    _clientList[id] = newEndpoint;
    _clientCount++;
    // TODO: Check if exist
    showClients();
}

// 1 SERVEUR, 2 CLIENTS SFML