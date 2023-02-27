/*
** EPITECH PROJECT, 2023
** UDPServer.cpp
** File description:
** UDPServer.cpp
*/

#include <iostream>
#include "saturnity/asio/udp/UDPServer.hpp"

namespace sa {
    sa::UDPServer::UDPServer(const std::shared_ptr<PacketRegistry> &packetRegistry,
                             const std::string &host, uint16_t port) :
            AbstractServer(packetRegistry, host, port)
    {
        // TODO: Implement UDP Server initialisation
        // TODO: add needed variables for server, and implement receive and send
//        _socket = boost::asio::ip::udp::socket(_ioCtx, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port));
        this->logger = *spdlog::stdout_color_mt("UDPServer");
    }

    void sa::UDPServer::receive() {
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
    };

    void sa::UDPServer::init()
    {
        this->logger.info("Initializing UDP server");
    }

    void sa::UDPServer::start() {
        asyncRead();
        this->run();
    }

    void sa::UDPServer::run() {
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
        if (!this->connections.contains(id)) {
            spdlog::warn("Tried to send data to a non-existing connection (id: {})", id);
            return;
        }
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

    void UDPServer::asyncRead() {
        if (this->_ioCtx.stopped()) {
            this->logger.error("IO context is dead");
            throw std::runtime_error("IO context is dead");
        }
        this->asyncReadPacketHeader();
    }

    void UDPServer::asyncReadPacketHeader() {
        std::array<byte_t, 4> header = {0, 0, 0, 0};

        _socket.async_receive_from(boost::asio::buffer(header, 4), _remote, [&, this](boost::system::error_code err, std::size_t len) {
            if (err) {
                this->logger.error("Failed to read packet header from server: {}", err.message());
                return;
            }
            if (len == 0) return this->asyncRead();
            if (len != 4) {
                this->logger.error("Failed to read packet header from server: {} bytes read instead of {}", len, 4);
            }
            std::uint16_t packetId = 0, packetSize = 0;
            std::memcpy(&packetId, header.data(), sizeof(std::uint16_t));
            std::memcpy(&packetSize, header.data() + sizeof(std::uint16_t), sizeof(std::uint16_t));
            if (packetId == 0 || packetSize == 0) {
                this->logger.warn("Failed to read packet header from server: packetId or packetSize is 0");
                return this->asyncRead();
            }
            this->asyncReadPacketBody(packetId, packetSize);
        });
    }

    void UDPServer::asyncReadPacketBody(std::uint16_t packetId, std::uint16_t packetSize) {
        this->logger.info("Reading packet {} body of size {} - ctx: {}", packetId, packetSize, this->_ioCtx.stopped());
        auto body = std::shared_ptr<byte_t>(new byte_t[packetSize], std::default_delete<byte_t[]>()); // NOLINT
        this->_ioCtx.poll();
        this->_socket.async_receive_from(boost::asio::buffer(body.get(), packetSize), this->_remote, [&, packetSize, packetId](boost::system::error_code ec, std::size_t bytesTransferred) {
            if (ec) {
                this->logger.error("Failed to read packet body from server: {}", ec.message());
                return;
            }
            if (bytesTransferred != packetSize) {
                this->logger.error("Failed to read packet body from server: {} bytes read instead of {}", bytesTransferred, packetSize);
                return asyncRead();
            }
            this->logger.info("Received packet {} of size {}", packetId, packetSize);
            auto buffer = ByteBuffer(body.get(), packetSize);
            this->handlePacketData(packetId, buffer);
            this->asyncRead();
        });
    }

    void UDPServer::handlePacketData(std::uint16_t packetId, ByteBuffer &buffer) {
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
