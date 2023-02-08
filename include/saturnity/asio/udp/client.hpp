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

namespace saturnity {

    class UdpClient {
    public:
        explicit UdpClient(std::string address, std::string port, boost::asio::io_context& ioContext);
        ~UdpClient();
        virtual void send();
        virtual void send(std::string input);
//        virtual void send(sa::AbstractPacket& packet);
        template<typename Packet>
        void send(const std::shared_ptr<Packet>& packet) {
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
            _socket.async_send_to(boost::asio::buffer(buffer.vector(), buffer.size()), _remoteEndpoint, boost::bind(&UdpClient::handleSend, this, boost::asio::placeholders::error));
    }

        void handleSend(const boost::system::error_code& error);
        void receive();
        void get_input();

        void handleReceive(const boost::system::error_code& error);
        // void clearBuff(std::array<char, BUFF_SIZE> buffer);
//        inline std::string getBuffer() { return std::string(_recvBuffer.data()); };
        inline boost::asio::ip::udp::endpoint getEndpoint() { return _remoteEndpoint; };

    private:
        boost::asio::ip::udp::endpoint _remoteEndpoint;
        boost::asio::io_context& _ioContext;
        boost::asio::ip::udp::resolver _resolver;
        boost::asio::ip::udp::resolver::query _query;

        boost::asio::ip::udp::socket _socket;
        std::array<byte_t, 4>  _recvBuffer;
        std::string _address;
        std::string _port;
        std::string _input;
    };
}  // namespace saturnity

#endif /* !CLIENT_HPP_ */
