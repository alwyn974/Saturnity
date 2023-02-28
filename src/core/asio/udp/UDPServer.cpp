/*
** EPITECH PROJECT, 2023
** UDPServer.cpp
** File description:
** UDPServer.cpp
*/

#include "saturnity/asio/udp/UDPServer.hpp"
#include <boost/asio/streambuf.hpp>
#include <iostream>

namespace sa {
    sa::UDPServer::UDPServer(const std::shared_ptr<PacketRegistry> &packetRegistry, const std::string &host, uint16_t port) :
        AbstractServer(packetRegistry, host, port),
        _workGuard(_ioCtx.get_executor()),
        _socket(_ioCtx, boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(host), port))
    {
        // TODO: Implement UDP Server initialisation
        // TODO: add needed variables for server, and implement receive and send
        //        _socket = boost::asio::ip::udp::socket(_ioCtx, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port));
        this->logger = *spdlog::stdout_color_mt("UDPServer");
    }

    /*void sa::UDPServer::receive()
    {
        // TODO: fix this, Print Receiving and Lambda (on first message) but doesn't recursive
        std::cout << "Receiving" << std::endl;
        std::cout << _ioCtx.stopped() << std::endl;
        std::array<byte_t, 4> header;
        _socket.async_receive_from(boost::asio::buffer(header, 4), _remote, [&, this](boost::system::error_code err, std::size_t len) {
            std::cout << "LAMBDA: " << len << std::endl;
            std::cout << this->_ioCtx.stopped() << std::endl;
            if (err) {
                std::cout << "ERROR: " << err.message() << std::endl;
            } else {
                std::cout << "test" << std::endl;
                std::cout.flush();
            }
        });
    };*/

    void sa::UDPServer::init()
    {
        this->logger.info("Initializing UDP server");
    }

    void sa::UDPServer::start()
    {
        _socket.set_option(boost::asio::ip::udp::socket::receive_buffer_size(65535));
        asyncRead();
    }

    void sa::UDPServer::run()
    {
        _ioCtx.run();
    }

    void sa::UDPServer::stop() {}

    void sa::UDPServer::broadcast(AbstractPacket &packet, int idToIgnore)
    {
        for (const auto &[id, con] : this->connections) {
            if (idToIgnore != -1 && idToIgnore == id) continue;
            sendTo(id, packet);
        }
    }

    void sa::UDPServer::sendTo(int id, const ByteBuffer &buffer)
    {
        try {
            this->_socket.send_to(boost::asio::buffer(buffer.getBuffer(), buffer.size()), this->_remote);
        } catch (std::exception &e) {
            this->logger.error("Failed to send data to client {}: {}", id, e.what());
        }
        /*if (!this->connections.contains(id)) {
            spdlog::warn("Tried to send data to a non-existing connection (id: {})", id);
            return;
        }*/
        // TODO: Implement
        //        if (this->onServerDataSent) this->onServerDataSent(this->connections[id], buffer);
    }

    void sa::UDPServer::disconnect(int id)
    {
        if (!this->connections.contains(id)) {
            spdlog::warn("Tried to disconnect a non-existing connection (id: {})", id);
            return;
        }
        // TODO: Implement
        if (this->onServerDisconnected) this->onServerDisconnected(this->connections[id]);
        this->connections.erase(id);
    }

    void sa::UDPServer::disconnect(int id, const std::string &reason)
    {
        if (!this->connections.contains(id)) {
            spdlog::warn("Tried to disconnect a non-existing connection (id: {})", id);
            return;
        }
        this->connections[id]->disconnect(reason);
    }

    void sa::UDPServer::disconnectAll()
    {
        for (const auto &[id, con] : this->connections) {
            con->disconnect();
        }
    }

    void UDPServer::asyncRead()
    {
        if (this->_ioCtx.stopped()) {
            this->logger.error("IO context is dead");
            throw std::runtime_error("IO context is dead");
        }
        this->asyncReadPacketHeader();
    }

    void UDPServer::asyncReadPacketHeader()
    {
        std::array<byte_t, 4> header = {0};
        _socket.async_receive_from(_streambuf.prepare(UINT16_MAX), _remote, [&, this](boost::system::error_code err, std::size_t len) {
            //            this->logger.info("Available: {}", _socket.available());
            if (err) {
                this->logger.error("Failed to read packet header from server: {}", err.message());
                return this->asyncRead();
            }
            if (len == 0) return this->asyncRead();
            auto bytes = reinterpret_cast<const byte_t *>(this->_streambuf.data().data()); // NOLINT
            //            std::memset(bytes, '\0', len);
            //            for (int i = 0; i < len; i++) {
            //                auto aled = this->buffer.data().data();
            //                this->logger.info("{}", *((byte_t *)(aled) + i));
            //            }
            //            boost::asio::buffer_copy(boost::asio::buffer(bytes, len), this->buffer.data());
            auto byteBuffer = ByteBuffer(bytes, len);

            const std::uint16_t packetId = byteBuffer.readUShort(), packetSize = byteBuffer.readUShort();

            if (packetId == 0 || packetSize == 0) {
                this->logger.warn("Failed to read packet header from server: packetId or packetSize is 0");
                return this->asyncRead();
            }
            _streambuf.consume(len);
            this->handlePacketData(packetId, byteBuffer);
            this->asyncRead();
            // this->asyncReadPacketBody(packetId, packetSize);
        });
    }

    void UDPServer::asyncReadPacketBody(std::uint16_t packetId, std::uint16_t packetSize)
    {
        this->logger.info("ALED PUTAIN {}", this->_ioCtx.stopped());
        this->logger.info("Reading packet {} body of size {} - ctx: {}", packetId, packetSize, this->_ioCtx.stopped());
        auto body = std::shared_ptr<byte_t>(new byte_t[packetSize], std::default_delete<byte_t[]>()); // NOLINT
        try {
            auto bytesTransferred = this->_socket.receive_from(boost::asio::buffer(body.get(), packetSize), _remote);
            this->logger.info("aled j'suis keblo");
            if (bytesTransferred != packetSize) {
                this->logger.error("Failed to read packet body from server: {} bytes read instead of {}", bytesTransferred, packetSize);
                return asyncRead();
            }
            this->logger.info("Received packet {} of size {}", packetId, packetSize);
            auto buffer = ByteBuffer(body.get(), packetSize);
            this->handlePacketData(packetId, buffer);
            this->asyncRead();
        } catch (boost::system::system_error &e) {
            this->logger.error("Failed to read packet body from server: {}", e.what());
        }
        //        this->logger.info("Available: {}", _socket.available());
        //        this->_socket.async_receive_from(boost::asio::buffer(body.get(), packetSize), this->_remote, [&, packetSize,
        //        packetId](boost::system::error_code ec, std::size_t bytesTransferred) {
        //            if (ec) {
        //                this->logger.error("Failed to read packet body from server: {}", ec.message());
        //                return;
        //            }
        //            if (bytesTransferred != packetSize) {
        //                this->logger.error("Failed to read packet body from server: {} bytes read instead of {}", bytesTransferred, packetSize);
        //                return asyncRead();
        //            }
        //            this->logger.info("Received packet {} of size {}", packetId, packetSize);
        //            auto buffer = ByteBuffer(body.get(), packetSize);
        //            this->handlePacketData(packetId, buffer);
        //            this->asyncRead();
        //        });
        //        this->logger.info("aled j'suis keblo");
    }

    void UDPServer::handlePacketData(std::uint16_t packetId, ByteBuffer &buffer)
    {
        if (!this->packetRegistry->hasPacket(packetId)) {
            this->logger.error("Received unknown packet with id {}", packetId);
            return;
        }
        if (!this->packetHandlers.contains(packetId)) {
            this->logger.error("Received packet with id {} but no handler is registered", packetId);
            return;
        }
        auto handler = this->packetHandlers[packetId];
        auto connection = std::make_shared<ConnectionToClient>(this->packetRegistry, -1, this->shared_from_this());
        handler(connection, buffer);
    }

} // namespace sa
