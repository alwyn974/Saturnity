/*
** EPITECH PROJECT, 2023
** UDPClient.cpp
** File description:
** UDPClient.cpp
*/

#include <iostream>
#include "saturnity/asio/udp/UDPClient.hpp"

namespace sa {
    UDPClient::UDPClient(const std::shared_ptr<PacketRegistry> &packetRegistry) : AbstractClient(packetRegistry), _socket(_ioContext)
    {
        this->logger = *spdlog::stdout_color_mt("UDPClient");
    }

    void UDPClient::init()
    {
        this->logger.info("Initializing UDP client");
        this->connection = std::make_shared<ConnectionToServer>(packetRegistry, this->shared_from_this());
        this->_ioContext.run();
    }

    void UDPClient::connect(const std::string &host, uint16_t port)
    {
        char *temp = static_cast<char *>(malloc(10));
        sprintf(temp, "%d", port);
        std::string portStr = std::string(temp);
        if (port < 0 || port > 65535) throw std::out_of_range("Invalid port number");
        boost::asio::ip::udp::resolver resolver(_ioContext);
        boost::asio::ip::udp::resolver::query mquery(boost::asio::ip::udp::v4(), host, portStr);
        this->_endpoint = boost::asio::ip::udp::endpoint(*resolver.resolve(mquery));
//                resolver.resolve(host, std::to_string(port));
        boost::system::error_code ec;
        _socket.open(boost::asio::ip::udp::v4());
        if (ec) {
            this->logger.error("Failed to connect to server: {}", ec.message());
            throw ClientCannotConnectException("Failed to connect to server: " + ec.message());
        }
        this->state = EnumClientState::CONNECTED;
        if (this->onClientConnected) this->onClientConnected(this->connection);
        this->logger.info("Connected to {} on port {}", _endpoint.address().to_string(), _endpoint.port());
        this->asyncRead();
    }

    void UDPClient::disconnect()
    {
        this->logger.info("Disconnecting from server");
        boost::system::error_code ec;
        this->_socket.shutdown(boost::asio::ip::udp::socket::shutdown_both, ec);
        this->_socket.close(ec);
        this->state = EnumClientState::DISCONNECTED;
        if (this->onClientDisconnected) this->onClientDisconnected(this->connection);
    }

    void UDPClient::send(ByteBuffer &buffer)
    {
        _socket.async_send_to(boost::asio::buffer(buffer.getBuffer()), _endpoint, [&](boost::system::error_code err, std::size_t len) {
//            this->logger.info("Sending {} to {}", buffer.getBuffer().data(), _endpoint.address().to_string());
            std::cout << "Sending data" << std::endl;
        });
        if (this->onClientDataSent) this->onClientDataSent(this->connection, buffer);
    }

    void UDPClient::onRead(boost::system::error_code &ec, std::size_t bytesTransferred)
    {
        if (ec) {
            this->logger.error("Failed to read from server: {}", ec.message());
            this->disconnect();
            return;
        }
        //        this->logger.info("Received {} bytes from server", bytesTransferred);
        /*if (this->onClientDataReceived)
            this->onClientDataReceived(this->connection, buffer);*/
    }

    void UDPClient::asyncRead()
    {
        std::array<byte_t, 18> data;
        this->_socket.async_receive(boost::asio::buffer(data, 18), [&](boost::system::error_code ec, std::size_t bytesTransferred) {
            if (ec) {
                this->logger.error("Failed to read from server: {}", ec.message());
                this->disconnect();
                return;
            }
            //this->logger.info("Received {} bytes from server", bytesTransferred);
            this->onRead(ec, bytesTransferred);
            this->asyncRead();
        });
        /*boost::asio::async_read(this->_socket, boost::asio::buffer(buffer.vector()), [this](boost::system::error_code ec, std::size_t bytesTransferred) {
            spdlog::info("asyncRead callback");
            if (ec) {
                this->logger.error("Failed to read from server: {}", ec.message());
                this->disconnect();
                return;
            }
            this->logger.info("Received {} bytes from server", bytesTransferred);
            this->onRead(ec, bytesTransferred);
            this->asyncRead();
        });*/

        /*this->_socket.async_read_some(boost::asio::buffer(buffer.vector(), 4), [this](boost::system::error_code ec, std::size_t bytesTransferred) {
            spdlog::info("asyncRead callback");
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
