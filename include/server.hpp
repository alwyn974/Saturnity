/*
** EPITECH PROJECT, 2023
** Saturnity
** File description:
** server
*/

#ifndef SERVER_HPP_
#define SERVER_HPP_

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <list>
#include <map>
#include "packets/packets.hpp"

#define BUFF_SIZE 10

void handleSend(const boost::system::error_code& error, boost::asio::mutable_buffer buffer, const boost::asio::ip::udp::socket& msocket,
                const boost::asio::io_service& ioService, std::string& input, boost::asio::ip::udp::endpoint remote);
namespace saturnity {
    class UdpServer {
    public:
        explicit UdpServer(boost::asio::io_service& io_service, int port);
        ~UdpServer();
        void createSocket(int port);
        bool handshake();
        virtual void send(std::string& input);
        virtual void send(boost::asio::ip::udp::endpoint remoteEndpoint, std::string& input);

        void receive();
        void handleReceive(const boost::system::error_code& error);
        void handleSend(const boost::system::error_code& error);
        void clearBuff(std::array<char, BUFF_SIZE> buffer);
        void addClient(boost::asio::ip::udp::endpoint newEndpoint, int id);
        inline void showClients() { for (int i = 0; i < _clientCount; i++) { std::cout << "[Client] - " << _clientList[i] << std::endl; }; };
        bool isInList(const boost::asio::ip::udp::endpoint newEndpoint);
        void broadcastAll(std::string& msg);
        void broadcast(boost::asio::ip::udp::endpoint sender, std::string& msg);

    private:
        boost::asio::io_context& _ioCtx;
        boost::asio::ip::udp::endpoint _remoteEndpoint;
        boost::asio::ip::udp::socket _socket;
        std::array<char, BUFF_SIZE> _sendBuffer;
        std::array<char, BUFF_SIZE> _recvBuffer;
        std::string _input;
        int _port;
        int _clientCount;
        std::unordered_map<int, boost::asio::ip::udp::endpoint> _clientList;
    };



    class TcpServer {
    public:
        explicit TcpServer(boost::asio::io_service& io_service, int port);
        ~TcpServer();
        void createSocket();
        bool handshake();
        virtual void send(std::string& input);
        virtual void send(boost::asio::ip::udp::endpoint remoteEndpoint, std::string& input);

        void receive();
        void handleReceive(const boost::system::error_code& error);
        void handleSend(const boost::system::error_code& error);
        void clearBuff(std::array<char, BUFF_SIZE> buffer);
        void addClient(boost::asio::ip::udp::endpoint newEndpoint, int id);
        inline void showClients() { for (int i = 0; i < _clientCount; i++) { std::cout << "[Client] - " << _clientList[i] << std::endl; }; };
        bool isInList(const boost::asio::ip::udp::endpoint newEndpoint);
        void broadcastAll(std::string& msg);
        void broadcast(boost::asio::ip::udp::endpoint sender, std::string& msg);

    private:
        boost::asio::io_context& _ioCtx;
        boost::asio::ip::udp::endpoint _remoteEndpoint;
        boost::asio::ip::udp::socket _socket;
        std::array<char, BUFF_SIZE> _sendBuffer;
        std::array<char, BUFF_SIZE> _recvBuffer;
        std::string _input;
        int _port;
        int _clientCount;
        std::unordered_map<int, boost::asio::ip::udp::endpoint> _clientList;
    };

}  // namespace saturnity

#endif /* !SERVER_HPP_ */
