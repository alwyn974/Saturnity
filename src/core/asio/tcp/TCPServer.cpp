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
        _workGuard(_ioContext.get_executor()),
        _acceptor(_ioContext, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
        _socket(_ioContext),
        _asyncRun(false)
    {
        this->logger = *spdlog::stdout_color_mt("TCPServer");
    }

    void TCPServer::init()
    {
        this->logger.info("Initializing server");
        if (this->onClientConnect == nullptr) throw sa::ex::CallbackNotSetException("onClientConnect callback is not set");
    }

    void TCPServer::run()
    {
        if (this->running) throw ex::AlreadyRunningException("Server is already running");
        this->logger.info("Running server");
        this->running = true;
        this->_ioContext.run();
    }

    void TCPServer::asyncRun()
    {
        if (this->_asyncRun) throw ex::AlreadyRunningException("Server is already running asynchronously");
        this->logger.info("Running asynchronously");
        this->_asyncRun = true;
        this->_runThread = std::thread([this] { this->run(); });
        this->_runThread.detach();
    }

    void TCPServer::start()
    {
        this->logger.info("Starting...");
        this->waitForConnection();
    }

    void TCPServer::stop()
    {
        this->logger.info("Stopping server");
        this->disconnectAll();
        boost::system::error_code ec;
        this->_acceptor.close(ec);
        if (ec) this->logger.error("Failed to close acceptor: {}", ec.message());
        this->_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
        if (ec) this->logger.error("Failed to shutdown socket: {}", ec.message());
        this->_socket.close(ec);
        if (ec) this->logger.error("Failed to close socket: {}", ec.message());
        this->_workGuard.reset();
        this->_ioContext.stop();
    }

    void TCPServer::waitForConnection()
    {
        auto casted = std::static_pointer_cast<TCPServer>(this->shared_from_this());
        this->_acceptor.async_accept([this, casted](boost::system::error_code ec, boost::asio::ip::tcp::socket socket) {
            if (ec) {
                this->logger.error("Failed to accept connection: {}", ec.message());
                return this->waitForConnection();
            }
            this->logger.info("New connection from {}:{}", socket.remote_endpoint().address().to_string(), socket.remote_endpoint().port());
            auto connection = TCPConnectionToClient::create(this->packetRegistry, -1, casted, std::move(socket));
            if (!this->onClientConnect(connection)) {
                this->logger.info("Connection refused");
                return this->waitForConnection();
            }
            const int id = this->nextId++;
            connection->setId(id);
            this->connections[id] = connection;
            if (this->onClientConnected) this->onClientConnected(connection);
            connection->start();
            this->waitForConnection();
        });
    }

    void TCPServer::broadcast(AbstractPacket &packet, int idToIgnore)
    {
        for (const auto &[id, con] : this->connections) {
            if (idToIgnore != -1 && idToIgnore == id) continue;
            sendTo(id, packet);
        }
    }

    void TCPServer::sendTo(int id, ByteBuffer &buffer)
    {
        if (!this->connections.contains(id)) {
            spdlog::warn("Tried to send data to a non-existing connection (id: {})", id);
            return;
        }
        this->connections[id]->send(buffer);
    }

    void TCPServer::disconnect(int id)
    {
        this->disconnect(id, "");
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
        for (const auto &[id, con] : this->connections)
            con->disconnect();
    }

    void TCPServer::clientDisconnected(const std::shared_ptr<TCPConnectionToClient> &client)
    {
        if (!this->connections.contains(client->getId())) {
            this->logger.warn("Tried to disconnect a non-existing connection (id: {})", client->getId());
            return;
        }
        auto con = this->connections[client->getId()];
        if (this->onClientDisconnected) this->onClientDisconnected(con);
        this->connections.erase(client->getId());
    }

    void TCPServer::clientSentPacket(const std::shared_ptr<TCPConnectionToClient> &client, std::uint16_t packetId, ByteBuffer &buffer)
    {
        if (!this->connections.contains(client->getId())) {
            this->logger.warn("Tried to send data to a non-existing connection (id: {})", client->getId());
            return;
        }
        auto con = this->connections[client->getId()];
        if (!this->packetRegistry->hasPacket(packetId)) {
            this->logger.error("Received unknown packet with id {}", packetId);
            return;
        }
        if (!this->packetHandlers.contains(packetId)) {
            this->logger.error("Received packet with id {} but no handler is registered", packetId);
            return;
        }
        auto handler = this->packetHandlers[packetId];
        handler(con, buffer);
    }
} // namespace sa
