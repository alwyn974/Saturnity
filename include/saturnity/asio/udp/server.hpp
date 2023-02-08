//
// Created by chatdo on 08/02/23.
//
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
#include <iostream>
#include <string>
#include <cstdint>
#include <optional>
#include "saturnity/Saturnity.hpp"


class PacketFactory {
public:

    static std::shared_ptr<PacketFactory> getFactory() {
        if (_factory == nullptr)
            _factory = std::make_shared<PacketFactory>();
        return _factory;
    }
    void registerPacket(std::uint16_t id, std::shared_ptr<sa::AbstractPacket> packetRef, std::function<std::shared_ptr<sa::AbstractPacket>(sa::ByteBuffer&)> creator) {
        if (_packetRegistry.contains(id))
            throw std::runtime_error("Packet already registered");
        _packetRegistry[id] = creator;
        _packetRef[id] = packetRef;
    }

    template<typename Packet>
    bool hasPacket() {
        for (const auto &[id, packet]: this->_packetRef) {
            auto pointer = std::dynamic_pointer_cast<Packet>(packet);
            if (pointer)
                return true;
        }
        return false;
    };

    bool hasPacket(std::uint16_t id)
    {
        return this->_packetRegistry.contains(id);
    }

    std::function<std::shared_ptr<sa::AbstractPacket>(sa::ByteBuffer&)> getPacket(std::uint16_t id)
    {
        return this->_packetRegistry[id];
    }

    template<typename Packet>
    std::optional<std::uint16_t> getPacketId() {
        for (const auto &[id, packet]: this->_packetRef) {
            auto pointer = std::dynamic_pointer_cast<Packet>(packet);
            if (pointer)
                return id;
        }
        return std::nullopt;
    }

    std::unordered_map<short, std::shared_ptr<sa::AbstractPacket>> _packetRef;

private:
    static std::shared_ptr<PacketFactory> _factory;
    std::unordered_map<short, std::function<std::shared_ptr<sa::AbstractPacket>(sa::ByteBuffer&)>> _packetRegistry;
};

namespace saturnity {
    class UdpServer {
    public:
        explicit UdpServer(boost::asio::io_context& ioCtx, int port);
        ~UdpServer();
        void createSocket(int port);
        bool handshake();
        virtual void send(std::string& input);
        virtual void send(boost::asio::ip::udp::endpoint remoteEndpoint, std::string& input);
        template<typename Packet>
        void send(const std::shared_ptr<Packet>& packet, boost::asio::ip::udp::endpoint remoteEndpoint) {
            sa::ByteBuffer buffer(128);
            static const auto factory = PacketFactory::getFactory();
            auto id = factory->getPacketId<Packet>();
            if (!id.has_value())
                throw std::runtime_error("Error template");
            buffer.writeUShort(id);
            buffer.writeUShort(0);
            packet.toBytes(buffer);
            buffer.setWriterIndex(sizeof(std::uint16_t));
            buffer.writeUShort(buffer.size() - (sizeof(std::uint16_t) * 2));
            buffer.setWriterIndex(buffer.size());
            _socket.async_send_to(boost::asio::buffer(buffer.getBuffer(), buffer.size()), remoteEndpoint, boost::bind(&UdpServer::handleSend, this, boost::asio::placeholders::error));
        }

        void send(sa::AbstractPacket& packet, std::uint16_t id, boost::asio::ip::udp::endpoint remoteEndpoint) {
            sa::ByteBuffer buffer(128);
            buffer.writeUShort(id);
            buffer.writeUShort(0);
            packet.toBytes(buffer);
            buffer.setWriterIndex(sizeof(std::uint16_t));
            buffer.writeUShort(buffer.size() - (sizeof(std::uint16_t) * 2));
            buffer.setWriterIndex(buffer.size());
            _socket.async_send_to(boost::asio::buffer(buffer.getBuffer(), buffer.size()), remoteEndpoint, boost::bind(&UdpServer::handleSend, this, boost::asio::placeholders::error));
        }

        void receive();
        void handleReceive(const boost::system::error_code& error);
        void handleSend(const boost::system::error_code& error);
//        void clearBuff(std::array<char, BUFF_SIZE> buffer);
        void addClient(boost::asio::ip::udp::endpoint newEndpoint, int id);
        inline void showClients() { for (int i = 0; i < _clientCount; i++) { std::cout << "[Client] - " << _clientList[i] << std::endl; }; };
        bool isInList(const boost::asio::ip::udp::endpoint newEndpoint);
        void broadcastAll(std::string& msg);

        void broadcast(boost::asio::ip::udp::endpoint sender, uint16_t id, sa::AbstractPacket& packet) {
            std::cout << "BROADCAST" << std::endl;

            for (const auto& [key, remote] : _clientList) {
                if (remote != sender)
                send(packet, id, remote);
            }
            receive();
        }

    private:
        boost::asio::io_context& _ioCtx;
        boost::asio::ip::udp::endpoint _remoteEndpoint;
        boost::asio::ip::udp::socket _socket;
        std::array<byte_t, 128>  _recvBuffer;
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
        void addClient(boost::asio::ip::udp::endpoint newEndpoint, int id);
        inline void showClients() { for (int i = 0; i < _clientCount; i++) { std::cout << "[Client] - " << _clientList[i] << std::endl; }; };
        bool isInList(const boost::asio::ip::udp::endpoint newEndpoint);
        void broadcastAll(std::string& msg);
        void broadcast(boost::asio::ip::udp::endpoint sender, std::string& msg);

    private:
        boost::asio::io_context& _ioCtx;
        boost::asio::ip::udp::endpoint _remoteEndpoint;
        boost::asio::ip::udp::socket _socket;
//        std::array<char, BUFF_SIZE> _sendBuffer;
//        std::array<char, BUFF_SIZE> _recvBuffer;
        std::string _input;
        int _port;
        int _clientCount;
        std::unordered_map<int, boost::asio::ip::udp::endpoint> _clientList;
    };

}  // namespace saturnity




#endif /* !SERVER_HPP_ */
