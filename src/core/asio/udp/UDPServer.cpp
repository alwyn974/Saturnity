/*
** EPITECH PROJECT, 2023
** UDPServer.cpp
** File description:
** UDPServer.cpp
*/

#include "saturnity/asio/udp/UDPServer.hpp"

namespace sa {
    sa::UDPServer::UDPServer(const std::shared_ptr<PacketRegistry> &packetRegistry, const std::string &host, uint16_t port) :
        AbstractServer(packetRegistry, host, port),
        _workGuard(_ioContext.get_executor()),
        _socket(_ioContext, boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(host), port)),
        _asyncRun(false)
    {
        this->logger = *spdlog::stdout_color_mt("UDPServer");
    }

    void sa::UDPServer::init()
    {
        this->logger.info("Initializing UDP server");
        if (this->onClientConnect == nullptr) throw sa::ex::CallbackNotSetException("onClientConnect callback is not set");
    }

    void sa::UDPServer::run()
    {
        if (this->running) throw ex::AlreadyRunningException("Server is already running");
        this->logger.info("Running server");
        this->running = true;
        this->_ioContext.run();
    }

    void sa::UDPServer::asyncRun()
    {
        if (this->_asyncRun) throw ex::AlreadyRunningException("Server is already running asynchronously");
        this->logger.info("Running asynchronously");
        this->_asyncRun = true;
        this->_runThread = std::thread([this] { this->run(); });
        this->_runThread.detach();
    }

    void sa::UDPServer::start()
    {
        this->logger.info("Starting...");
        this->asyncRead();
    }

    void sa::UDPServer::stop()
    {
        this->logger.info("Stopping server");
        this->disconnectAll();
        boost::system::error_code ec;
        if (ec) this->logger.error("Failed to close acceptor: {}", ec.message());
        this->_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
        if (ec) this->logger.error("Failed to shutdown socket: {}", ec.message());
        this->_socket.close(ec);
        if (ec) this->logger.error("Failed to close socket: {}", ec.message());
        this->_workGuard.reset();
        this->_ioContext.stop();
    }

    void UDPServer::asyncRead()
    {
        auto buffer = std::shared_ptr<byte_t>(new byte_t[this->getMaxBufferSize()], std::default_delete<byte_t[]>()); // NOLINT
        this->_socket.async_receive_from(
            boost::asio::buffer(buffer.get(), this->getMaxBufferSize()), this->_remoteEndpoint,
            [this, buffer](const boost::system::error_code &ec, std::size_t bytesTransferred) {
                int clientId = this->getClientId(this->_remoteEndpoint);
                if (ec) {
                    this->logger.error("Failed to read data: {}", ec.message());
                    if (clientId != -1) {
                        auto client = std::static_pointer_cast<UDPConnectionToClient>(this->connections[clientId]);
                        this->clientDisconnected(client);
                    }
                    return this->asyncRead();
                }
                if (clientId == -1) {
                    auto server = std::static_pointer_cast<UDPServer>(this->shared_from_this());
                    auto client = UDPConnectionToClient::create(this->packetRegistry, -1, server, &this->_socket, this->_remoteEndpoint);
                    if (!this->onClientConnect(client)) {
                        this->logger.info("Connection refused");
                        return this->asyncRead();
                    }
                    client->setId(this->nextId++);
                    this->connections[client->getId()] = client;
                    client->start();
                    clientId = client->getId();
                }
                if (bytesTransferred == 0) return this->asyncRead();
                std::uint16_t packetId = 0, packetSize = 0;
                std::memcpy(&packetId, buffer.get(), sizeof(std::uint16_t));
                std::memcpy(&packetSize, buffer.get() + sizeof(std::uint16_t), sizeof(std::uint16_t));
                if (packetId == 0 || packetSize == 0) {
                    this->logger.warn("Failed to read packet header from server: packetId or packetSize is 0");
                    return this->asyncRead();
                }
                auto &client = this->connections[clientId];
                ByteBuffer byteBuffer(buffer.get() + (sizeof(std::uint16_t) * 2), packetSize);
                if (this->onServerDataReceived) this->onServerDataReceived(client, packetId, packetSize, byteBuffer);
                this->handlePacketData(client, packetId, byteBuffer);
                this->asyncRead();
            });
    }

    void sa::UDPServer::broadcast(AbstractPacket &packet, int idToIgnore)
    {
        for (const auto &[id, con] : this->connections) {
            if (idToIgnore != -1 && idToIgnore == id) continue;
            sendTo(id, packet);
        }
    }

    void sa::UDPServer::sendTo(int id, ByteBuffer &buffer)
    {
        if (!this->connections.contains(id)) {
            spdlog::warn("Tried to send data to a non-existing connection (id: {})", id);
            return;
        }
        this->connections[id]->send(buffer);
    }

    void sa::UDPServer::disconnect(int id)
    {
        this->disconnect(id, "");
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
        for (const auto &[id, con] : this->connections)
            con->disconnect();
    }

    int UDPServer::getClientId(boost::asio::ip::udp::endpoint &endpoint)
    {
        for (const auto &[id, con] : this->connections) {
            auto client = std::dynamic_pointer_cast<UDPConnectionToClient>(con);
            if (client->getEndpoint() == endpoint) return id;
        }
        return -1;
    }

    void UDPServer::clientDisconnected(const std::shared_ptr<UDPConnectionToClient> &client)
    {
        if (!this->connections.contains(client->getId())) {
            this->logger.warn("Tried to disconnect a non-existing connection (id: {})", client->getId());
            return;
        }
        auto con = this->connections[client->getId()];
        if (this->onClientDisconnected) this->onClientDisconnected(con);
        this->connections.erase(client->getId());
    }

    void UDPServer::handlePacketData(const std::shared_ptr<ConnectionToClient> &client, uint16_t packetId, ByteBuffer &buffer)
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
