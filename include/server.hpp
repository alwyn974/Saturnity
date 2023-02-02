/*
** EPITECH PROJECT, 2023
** Saturnity
** File description:
** server
*/

#ifndef SERVER_HPP_
#define SERVER_HPP_

#include "packets/packets.hpp"
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <list>

#define BUFF_SIZE 1

namespace saturnity {
    class UdpServer {
    public:
        explicit UdpServer(int port);
        ~UdpServer();
        void createSocket(int port);
        bool handshake();
        void send();
        void receive();
        void handleReceive(const boost::system::error_code& error);
        void handleSend(const boost::system::error_code& error, std::array<char, BUFF_SIZE> sendBuffer);
        void clearBuff(std::array<char, BUFF_SIZE> buffer);

    private:
        boost::asio::io_context _ioCtx;
        boost::asio::ip::udp::endpoint _remoteEndpoint;
        boost::asio::ip::udp::socket _socket;
        std::array<char, BUFF_SIZE> _sendBuffer;
        std::array<char, BUFF_SIZE> _recvBuffer;

        //        char _sendBuffer[BUFF_SIZE];
        //        char _recvBuffer[BUFF_SIZE];
        int _port;


    };

    class TcpServer {
    public:
        TcpServer();
        ~TcpServer();
        int createSocket();
        bool handshake();
        void send(Packet toSend);
        void receive();
        void handleReceive();
        void handleSend();
    private:
        boost::asio::io_context _io_ctx;
        boost::asio::ip::udp::endpoint _remote_endpoint;
        boost::asio::ip::udp::socket _socket;
//        char _buffer[1024];
        int _port;
        int _address;

    };


//    inline std::list<std::string> getPlayerList(){return _playerList;};
//    void addPlayer();
//    void disconnectPlayer();
//    void movePlayer();
//
//private:
//    std::list<std::string> _playerList;

}  // namespace saturnity::Server

#endif /* !SERVER_HPP_ */
