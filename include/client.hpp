/*
** EPITECH PROJECT, 2023
** Saturnity
** File description:
** client
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <list>

#include "packets/packets.hpp"

#define BUFF_SIZE 10

namespace saturnity {

    class UdpClient {
    public:
        explicit UdpClient(std::string address, std::string port, boost::asio::io_context& ioContext);
        ~UdpClient();
        virtual void send();
        virtual void send(std::string input);
        virtual void send(std::vector<uint8_t> input);

        void handleSend(const boost::system::error_code& error);
        void receive();
        void get_input();

        void handleReceive(const boost::system::error_code& error);
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
    };
}  // namespace saturnity

#endif /* !CLIENT_HPP_ */
