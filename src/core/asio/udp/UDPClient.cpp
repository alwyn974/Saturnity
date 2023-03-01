/*
** EPITECH PROJECT, 2023
** UDPClient.cpp
** File description:
** UDPClient.cpp
*/

#include "saturnity/asio/udp/UDPClient.hpp"

namespace sa {
    UDPClient::UDPClient(const std::shared_ptr<PacketRegistry> &packetRegistry) :
        AbstractClient(packetRegistry),
        _workGuard(_ioContext.get_executor()),
        _socket(_ioContext),
        _asyncRun(false)
    {
        this->logger = *spdlog::stdout_color_mt("UDPClient");
    }

    void UDPClient::init()
    {
        this->logger.info("Initializing UDP client");
        this->connection = std::make_shared<ConnectionToServer>(packetRegistry, this->shared_from_this());
    }

    void UDPClient::run()
    {
        if (this->running) throw ex::AlreadyRunningException("Client is already running");
        this->logger.info("Running client");
        this->running = true;
        this->_ioContext.run();
    }

    void UDPClient::asyncRun()
    {
        if (this->_asyncRun) throw ex::AlreadyRunningException("Client is already running asynchronously");
        this->logger.info("Running client asynchronously");
        this->_asyncRun = true;
        this->_runThread = std::thread([this] { this->run(); });
        this->_runThread.detach();
    }

    void UDPClient::stop()
    {
        this->logger.info("Stopping client");
        if (this->state != EnumClientState::DISCONNECTED) this->disconnect();
        this->_workGuard.reset();
        this->_ioContext.stop();
        if (_asyncRun && this->_runThread.joinable()) this->_runThread.join();
        this->running = false;
        this->_asyncRun = false;
    }

    void UDPClient::connect(const std::string &host, uint16_t port)
    {
        if (static_cast<std::int16_t>(port) < 0) throw std::out_of_range("Port number is negative");
        auto resolver = boost::asio::ip::udp::resolver(_ioContext);
        auto query = boost::asio::ip::udp::resolver::query(boost::asio::ip::udp::v4(), host, std::to_string(port));
        this->_endpoints = resolver.resolve(query);

        this->logger.info("Connecting to {} on port {}", host, port);
        boost::system::error_code ec;
        boost::asio::connect(this->_socket, this->_endpoints, ec);

        if (ec) {
            this->logger.error("Failed to connect to server: {}", ec.message());
            throw ClientCannotConnectException("Failed to connect to server: " + ec.message());
        }

        // As UDP is connectionless, there is no need to connect the socket
        this->state = EnumClientState::CONNECTED;
        if (this->onClientConnected) this->onClientConnected(this->connection);
        this->logger.info("Connected to {} on port {}", host, port);
        this->asyncRead();
    }

    void UDPClient::disconnect(bool forced)
    {
        this->logger.info("Disconnecting from server");
        boost::system::error_code ec;
        this->_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
        if (ec) this->logger.error("Failed to shutdown socket: {}", ec.message());
        this->_socket.close(ec);
        if (ec) this->logger.error("Failed to close socket: {}", ec.message());
        this->state = EnumClientState::DISCONNECTED;
        if (this->onClientDisconnected) this->onClientDisconnected(this->connection, forced);
        this->_ioContext.reset();
        this->_sendQueue.clear();
        this->logger.info("Disconnected from server");
    }

    void UDPClient::send(const ByteBuffer &buffer)
    {
        const bool queueEmpty = this->_sendQueue.empty();
        this->_sendQueue.push(buffer);
        if (this->_ioContext.stopped()) {
            this->logger.error("IO context is dead");
            throw ex::IOContextDeadException("IO context is dead");
        }

        if (queueEmpty) this->asyncSend();
    }

    void UDPClient::asyncSend()
    {
        if (this->_sendQueue.empty()) return;
        if (this->_ioContext.stopped()) return this->logger.error("IO context is stopped");
        auto &buffer = this->_sendQueue.front();
        this->_socket.async_send(boost::asio::buffer(buffer.getBuffer()), [&](boost::system::error_code ec, std::size_t bytesTransferred) {
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

    void UDPClient::asyncRead()
    {
        if (this->_ioContext.stopped()) {
            this->logger.error("IO context is dead");
            throw ex::IOContextDeadException("IO context is dead");
        }
        auto buffer = std::shared_ptr<byte_t>(new byte_t[this->getMaxBufferSize()], std::default_delete<byte_t[]>()); // NOLINT
        this->_socket.async_receive(
            boost::asio::buffer(buffer.get(), this->getMaxBufferSize()), [this, buffer](boost::system::error_code ec, std::size_t bytesTransferred) {
                if (ec) {
                    this->logger.error("Failed to read packet data from server: {}", ec.message());
                    this->disconnect(true);
                    return;
                }
                if (bytesTransferred == 0) return this->asyncRead();
                std::uint16_t packetId = 0, packetSize = 0;
                std::memcpy(&packetId, buffer.get(), sizeof(std::uint16_t));
                std::memcpy(&packetSize, buffer.get() + sizeof(std::uint16_t), sizeof(std::uint16_t));
                if (packetId == 0 || packetSize == 0) {
                    this->logger.warn("Failed to read packet header from server: packetId or packetSize is 0");
                    return this->asyncRead();
                }
                ByteBuffer byteBuffer(buffer.get() + (sizeof(std::uint16_t) * 2), packetSize);
                if (this->onClientDataReceived) this->onClientDataReceived(this->connection, packetId, packetSize, byteBuffer);
                this->handlePacketData(packetId, byteBuffer);
                this->asyncRead();
            });
    }

    void UDPClient::handlePacketData(std::uint16_t packetId, ByteBuffer &buffer)
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
