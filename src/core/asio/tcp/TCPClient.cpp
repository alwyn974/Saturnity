/*
** EPITECH PROJECT, 2023
** TCPClient.cpp
** File description:
** TCPClient.cpp
*/

#include "saturnity/asio/tcp/TCPClient.hpp"

namespace sa {
    TCPClient::TCPClient(const std::shared_ptr<PacketRegistry> &packetRegistry) : AbstractClient(packetRegistry), _socket(_ioContext)
    {
        this->logger = *spdlog::stdout_color_mt("TCPClient");
    }

    void TCPClient::init()
    {
        this->logger.info("Initializing TCP client");
        this->connection = std::make_shared<ConnectionToServer>(packetRegistry, this->shared_from_this());
        this->_ioContext.run();
    }

    void TCPClient::connect(const std::string &host, uint16_t port)
    {
        if (port < 0 || port > 65535)
            throw std::out_of_range("Invalid port number");
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
        if (this->onClientConnected)
            this->onClientConnected(this->connection);
        this->logger.info("Connected to {} on port {}", host, port);
        this->asyncRead();
    }

    void TCPClient::disconnect()
    {
        this->logger.info("Disconnecting from server");
        boost::system::error_code ec;
        this->_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
        this->_socket.close(ec);
        this->state = EnumClientState::DISCONNECTED;
        if (this->onClientDisconnected)
            this->onClientDisconnected(this->connection);
    }

    void TCPClient::send(ByteBuffer &buffer)
    {
        // TODO: Implement
        this->_socket.send(boost::asio::buffer(buffer.getBuffer()));

        if (this->onClientDataSent)
            this->onClientDataSent(this->connection, buffer);
    }

    void TCPClient::onRead(boost::system::error_code &ec, std::size_t bytesTransferred)
    {

    }

    void TCPClient::asyncRead()
    {
        /*this->_socket.async_read_some(boost::asio::buffer(this->_buffer, 1024), [this](boost::system::error_code ec, std::size_t bytesTransferred) {
            if (ec) {
                this->logger.error("Failed to read from server: {}", ec.message());
                this->disconnect();
                return;
            }
            this->logger.info("Received {} bytes from server", bytesTransferred);
            this->onRead(ec, bytesTransferred);
            this->asyncRead();
        });*/
    }
} // namespace sa
