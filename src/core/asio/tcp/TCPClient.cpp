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
        this->logger.info("Initializing TCP client");
        this->connection = std::make_shared<ConnectionToServer>(packetRegistry, this->shared_from_this());
    }

    void TCPClient::run()
    {
        this->logger.info("Running client");
        this->_ioContext.run();
    }

    void TCPClient::connect(const std::string &host, uint16_t port)
    {
        if (port < 0 || port > 65535) throw std::out_of_range("Invalid port number");
        auto resolver = boost::asio::ip::tcp::resolver(_ioContext);
        this->_endpoints = resolver.resolve(host, std::to_string(port));

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
        this->_socket.close(ec);
        this->state = EnumClientState::DISCONNECTED;
        if (this->onClientDisconnected) this->onClientDisconnected(this->connection, forced);
        this->_workGuard.reset();
    }

    void TCPClient::send(ByteBuffer &buffer)
    {
        const bool queueEmpty = this->_sendQueue.empty();
        this->_sendQueue.push(buffer);
        if (this->_ioContext.stopped()) this->logger.error("IO context is stopped");

        if (queueEmpty) this->asyncSend();
    }

    void TCPClient::asyncSend()
    {
        if (this->_sendQueue.empty()) return;
        if (this->_ioContext.stopped()) return this->logger.error("IO context is stopped");
        auto &buffer = this->_sendQueue.front();
        this->_socket.async_send(boost::asio::buffer(buffer.getBuffer()), [&](boost::system::error_code ec, std::size_t bytesTransferred) {
            this->logger.info("Send Queue: {}", this->_sendQueue.size());
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
        /*std::array<byte_t, 18> data;
        this->_socket.async_read_some(boost::asio::buffer(data, 18), [&](boost::system::error_code ec, std::size_t bytesTransferred) {
            if (ec) {
                this->logger.error("Failed to read from server: {}", ec.message());
                this->disconnect();
                return;
            }
            this->logger.info("Received {} bytes from server", bytesTransferred);
            this->asyncRead();
        });*/
    }
} // namespace sa
