/*
** EPITECH PROJECT, 2023
** UDPServer.cpp
** File description:
** UDPServer.cpp
*/

#include <iostream>
#include "saturnity/asio/udp/UDPServer.hpp"
#include <boost/asio/streambuf.hpp>
#include <iostream>

namespace sa {
    sa::UDPServer::UDPServer(const std::shared_ptr<PacketRegistry> &packetRegistry, const std::string &host, uint16_t port) :
        AbstractServer(packetRegistry, host, port),
        _workGuard(_ioCtx.get_executor()),
        _socket(_ioCtx, boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(host), port))
    {
        this->logger = *spdlog::stdout_color_mt("UDPServer");
    }

    void sa::UDPServer::init()
    {
        this->logger.info("Initializing UDP server");
    }

    void sa::UDPServer::start()
    {
        this->logger.info("Starting...");
//        this->asyncRead();
    }

    void sa::UDPServer::run()
    {
        this->logger.info("Running server");
        this->_ioCtx.run();
    }

//    void UDPServer::asyncRead()
//    {
//        if (this->_ioCtx.stopped()) {
//            this->logger.error("IO context is dead");
//            throw std::runtime_error("IO context is dead");
//        }
//    }

    void sa::UDPServer::asyncRun()
    {
        if (this->_asyncRun) throw ex::AlreadyRunningException("Server is already running asynchronously");
        this->logger.info("Running asynchronously");
        this->_asyncRun = true;
        this->_runThread = std::thread([this] { this->run(); });
        this->_runThread.detach();
    }

    void sa::UDPServer::stop() {
        this->logger.info("Stopping server");
        this->disconnectAll();
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
        try {
            this->_socket.send_to(boost::asio::buffer(buffer.getBuffer(), buffer.size()), this->_remote);
        } catch (std::exception &e) {
            this->logger.error("Failed to send data to client {}: {}", id, e.what());
        }
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
        for (const auto &[id, con] : this->connections) {
            con->disconnect();
        }
    }

    void UDPServer::clientSentPacket(const std::shared_ptr<UDPConnectionToClient> &client, std::uint16_t packetId, ByteBuffer &buffer)
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
