/*
** EPITECH PROJECT, 2023
** TCPServer.cpp
** File description:
** TCPServer.cpp
*/

#include "saturnity/asio/tcp/TCPServer.hpp"

namespace sa {
    TCPServer::TCPServer(const std::shared_ptr<PacketRegistry> &packetRegistry, const std::string &host, uint16_t port) :
        AbstractServer(packetRegistry, host, port),
        _acceptor(_ioContext, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
        _socket(_ioContext),
        _workGuard(_ioContext.get_executor())
    {
        this->logger = *spdlog::stdout_color_mt("TCPServer");
    }

    void TCPServer::init()
    {
        this->logger.info("Initializing server");
        if (this->onClientConnect == nullptr)
            throw sa::ex::CallbackNotSetException("onClientConnect callback is not set");
    }

    void TCPServer::run()
    {
        this->logger.info("Running server");
        this->_ioContext.run();
    }

    void TCPServer::start()
    {

    }

    void TCPServer::stop()
    {
        this->logger.info("Stopping server");
        this->disconnectAll();
        boost::system::error_code ec;
        this->_acceptor.close(ec);
        if (ec)
            this->logger.error("Failed to close acceptor: {}", ec.message());
        this->_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
        if (ec)
            this->logger.error("Failed to shutdown socket: {}", ec.message());
        this->_socket.close(ec);
        if (ec)
            this->logger.error("Failed to close socket: {}", ec.message());
        this->_workGuard.reset();
        this->_ioContext.stop();
    }

    void TCPServer::broadcast(AbstractPacket &packet, int idToIgnore)
    {
        for (const auto &[id, con]: this->connections) {
            if (idToIgnore != -1 && idToIgnore == id)
                continue;
            sendTo(id, packet);
        }
    }

    void TCPServer::sendTo(int id, const ByteBuffer &buffer)
    {
        if (!this->connections.contains(id)) {
            spdlog::warn("Tried to send data to a non-existing connection (id: {})", id);
            return;
        }
        // TODO(alwyn974): Implement
        // if (this->onServerDataSent) this->onServerDataSent(this->connections[id], buffer);
    }

    void TCPServer::disconnect(int id)
    {
        if (!this->connections.contains(id)) {
            spdlog::warn("Tried to disconnect a non-existing connection (id: {})", id);
            return;
        }
        // TODO(alwyn974): Implement
        if (this->onClientDisconnected)
            this->onClientDisconnected(this->connections[id]);
        this->connections.erase(id);
    }

    void TCPServer::disconnect(int id, const std::string &reason)
    {
        if (!this->connections.contains(id)) {
            spdlog::warn("Tried to disconnect a non-existing connection (id: {})", id);
            return;
        }
        this->connections[id]->disconnect(reason);
    }

    void TCPServer::disconnectAll()
    {
        for (const auto &[id, con]: this->connections)
            con->disconnect();
    }
} // namespace sa
