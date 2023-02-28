/*
** EPITECH PROJECT, 2023
** TCPClient.cpp
** File description:
** TCPClient.cpp
*/

#include "saturnity/asio/tcp/TCPClient.hpp"

namespace sa {
    TCPClient::TCPClient(const std::shared_ptr<PacketRegistry> &packetRegistry) :
        AbstractClient(packetRegistry),
        _workGuard(_ioContext.get_executor()),
        _socket(_ioContext)
    {
        this->logger = *spdlog::stdout_color_mt("TCPClient");
    }

    void TCPClient::init()
    {
        this->logger.info("Initializing client");
        this->connection = std::make_shared<ConnectionToServer>(packetRegistry, this->shared_from_this());
    }

    void TCPClient::run()
    {
        this->logger.info("Running client");
        this->_ioContext.run();
    }

    void TCPClient::connect(const std::string &host, uint16_t port)
    {
        if (static_cast<std::int16_t>(port) < 0) throw std::out_of_range("Port number can't be negative");
        auto resolver = boost::asio::ip::tcp::resolver(_ioContext);
        this->_endpoints = resolver.resolve(host, std::to_string(port));
        // TODO: add running state and others
        this->logger.info("Connecting to {} on port {}", host, port);
        boost::system::error_code ec;
        boost::asio::connect(this->_socket, this->_endpoints, ec);
        if (ec) {
            this->logger.error("Failed to connect to server: {}", ec.message());
            throw ClientCannotConnectException("Failed to connect to server: " + ec.message());
        }
        this->state = EnumClientState::CONNECTED;
        if (this->onClientConnected) this->onClientConnected(this->connection);
        this->logger.info("Connected to {} on port {}", host, port);
        this->asyncRead();
    }

    void TCPClient::disconnect(bool forced)
    {
        this->logger.info("Disconnecting from server");
        boost::system::error_code ec;
        this->_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
        if (ec) this->logger.error("Failed to shutdown socket: {}", ec.message());
        this->_socket.close(ec);
        if (ec) this->logger.error("Failed to close socket: {}", ec.message());
        this->state = EnumClientState::DISCONNECTED;
        if (this->onClientDisconnected) this->onClientDisconnected(this->connection, forced);
        this->_workGuard.reset();
    }

    void TCPClient::send(const ByteBuffer &buffer)
    {
        const bool queueEmpty = this->_sendQueue.empty();
        this->_sendQueue.push(buffer);
        if (this->_ioContext.stopped()) {
            this->logger.error("IO context is dead");
            throw ex::IOContextDeadException("IO context is dead");
        }

        if (queueEmpty) this->asyncSend();
    }

    void TCPClient::asyncSend()
    {
        if (this->_sendQueue.empty()) return;
        if (this->_ioContext.stopped()) return this->logger.error("IO context is stopped");
        auto &buffer = this->_sendQueue.front();
        this->_socket.async_send(boost::asio::buffer(buffer.getBuffer()), [this, &buffer](boost::system::error_code ec, std::size_t bytesTransferred) {
            if (ec) {
                this->logger.error("Failed to send data to server: {}", ec.message());
                this->disconnect(true);
                return;
            }
            if (bytesTransferred != buffer.size()) {
                this->logger.warn("Failed to send all data to server: {} bytes sent instead of {}", bytesTransferred, buffer.size());
                return;
            }
            if (this->onClientDataSent) this->onClientDataSent(this->connection, buffer);
            if (!this->_sendQueue.pop()) this->logger.error("Failed to pop from send queue");
            this->asyncSend();
        });
    }

    void TCPClient::asyncRead()
    {
        if (this->_ioContext.stopped()) {
            this->logger.error("IO context is dead");
            throw ex::IOContextDeadException("IO context is dead");
        }
        this->asyncReadPacketHeader();
    }

    void TCPClient::asyncReadPacketHeader()
    {
        auto header = std::shared_ptr<byte_t>(new byte_t[AbstractPacket::HEADER_SIZE], std::default_delete<byte_t[]>()); // NOLINT
        this->_socket.async_read_some(
            boost::asio::buffer(header.get(), AbstractPacket::HEADER_SIZE), [this, header](boost::system::error_code ec, std::size_t bytesTransferred) {
                this->logger.info("available: {}", this->_socket.available());
                if (ec) {
                    this->logger.error("Failed to read packet header from server: {}", ec.message());
                    this->disconnect();
                    return;
                }
                if (bytesTransferred == 0) return this->asyncRead();
                if (bytesTransferred != AbstractPacket::HEADER_SIZE) {
                    this->logger.error("Failed to read packet header from server: {} bytes read instead of {}", bytesTransferred, AbstractPacket::HEADER_SIZE);
                    return this->asyncRead();
                }
                std::uint16_t packetId = 0, packetSize = 0;
                std::memcpy(&packetId, header.get(), sizeof(std::uint16_t));
                std::memcpy(&packetSize, header.get() + sizeof(std::uint16_t), sizeof(std::uint16_t));
                if (packetId == 0 || packetSize == 0) {
                    this->logger.warn("Failed to read packet header from server: packetId or packetSize is 0");
                    return this->asyncRead();
                }
                this->asyncReadPacketBody(packetId, packetSize);
            });
    }

    void TCPClient::asyncReadPacketBody(std::uint16_t packetId, std::uint16_t packetSize)
    {
        this->logger.info("Reading packet {} body of size {}", packetId, packetSize);
        auto body = std::shared_ptr<byte_t>(new byte_t[packetSize], std::default_delete<byte_t[]>()); // NOLINT
        this->_socket.async_read_some(
            boost::asio::buffer(body.get(), packetSize), [&, packetSize, packetId, body](boost::system::error_code ec, std::size_t bytesTransferred) {
                if (ec) {
                    this->logger.error("Failed to read packet body from server: {}", ec.message());
                    this->disconnect();
                    return;
                }
                if (bytesTransferred != packetSize) {
                    this->logger.error("Failed to read packet body from server: {} bytes read instead of {}", bytesTransferred, packetSize);
                    this->disconnect();
                    return;
                }
                this->logger.info("Received packet {} of size {}", packetId, packetSize);
                auto buffer = ByteBuffer(body.get(), packetSize);
                if (this->onClientDataReceived) this->onClientDataReceived(this->connection, packetId, packetSize, buffer);
                this->handlePacketData(packetId, buffer);
                this->asyncRead();
            });
    }

    void TCPClient::handlePacketData(std::uint16_t packetId, ByteBuffer &buffer)
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
        handler(this->connection, buffer);
    }
} // namespace sa
