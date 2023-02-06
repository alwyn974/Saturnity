/*
** EPITECH PROJECT, 2023
** Saturnity
** File description:
** client
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include "packets/packets.hpp"
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <list>

#define BUFF_SIZE 10

namespace saturnity {

    class UdpClient {
    public:
        explicit UdpClient(std::string address, std::string port, boost::asio::io_context& ioContext);
        ~UdpClient();
        // bool handshake();
        virtual void send();
        // virtual void send(std::string input);
        void handleSend(const boost::system::error_code& error);
        void receive();
        void handleReceive(const boost::system::error_code& error, std::string& received);
        // void clearBuff(std::array<char, BUFF_SIZE> buffer);

    private:
        boost::asio::ip::udp::endpoint _remoteEndpoint;
        boost::asio::io_context& _ioContext;
        boost::asio::ip::udp::resolver _resolver;
        boost::asio::ip::udp::resolver::query _query;

        boost::asio::ip::udp::socket _socket;
        std::array<char, BUFF_SIZE> _sendBuffer;
        std::array<char, BUFF_SIZE> _recvBuffer;
        std::string _address;
        std::string _port;
        std::string _input;
        //        char _sendBuffer[BUFF_SIZE];
        //        char _recvBuffer[BUFF_SIZE];
    };
}

#endif /* !CLIENT_HPP_ */
