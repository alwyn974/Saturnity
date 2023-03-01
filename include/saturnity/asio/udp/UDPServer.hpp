/*
** EPITECH PROJECT, 2023
** UDPServer.hpp
** File description:
** UDPServer.hpp
*/

#ifndef SATURNITY_UDPSERVER_HPP
#define SATURNITY_UDPSERVER_HPP

#include "AbstractUDPProtocol.hpp"
#include "saturnity/core/network/server/AbstractServer.hpp"
#include "UDPConnectionToClient.hpp"
#include <spdlog/sinks/stdout_color_sinks.h>
#include <boost/asio.hpp>
#include <unordered_map>

/**
 * @brief The saturnity namespace.
 */
namespace sa {
    /**
     * @brief UDP server implementation with boost::asio.
     * @throws sa::ex::IOContextDeadException if the ioContext is dead. (send & read)
     */
    class UDPServer
        : public AbstractServer,
          public AbstractUDPProtocol {
    public:
        friend class UDPConnectionToClient;

        /**
         * @brief Create a new UDP server.
         * @param packetRegistry the packet registry.
         * @param host the host.
         * @param port the port.
         * @return the UDP server.
         */
        static std::shared_ptr<UDPServer> create(
            const std::shared_ptr<PacketRegistry> &packetRegistry, const std::string &host = "0.0.0.0", uint16_t port = 2409)
        {
            return std::shared_ptr<UDPServer>(new UDPServer(packetRegistry, host, port));
        }

        /**
         * @brief Instanciate the server
         */
        void init() override;

        /**
         * @brief Run the server. (blocking)
         * Run the ioContext.
         * @throws sa::ex::AlreadyRunningException if the server is already running.
         */
        void run() override;

        /**
         * @brief Run the server. (non-blocking)
         * Run the ioContext.
         * @throws sa::ex::AlreadyRunningException if the server is already running.
         */
        void asyncRun();

        /**
         * @brief Start the server.
         */
        void start() override;

        /**
         * @brief Stop the server.
         */
        void stop() override;

        /**
         * @brief Broadcast a packet to all clients.
         * @param packet the packet.
         * @param idToIgnore the id to ignore. (-1 to ignore no one)
         * @throws sa::ex::IOContextDeadException if the ioContext is dead.
         */
        void broadcast(AbstractPacket &packet, int idToIgnore) override;

        /**
         * @brief Broadcast a packet to all clients.
         * @param packet the packet.
         * @param idToIgnore the id to ignore. (-1 to ignore no one)
         * @throws sa::ex::IOContextDeadException if the ioContext is dead.
         */
        void broadcast(const std::shared_ptr<AbstractPacket> &packet, int idToIgnore) override { AbstractServer::broadcast(packet, idToIgnore); }

        /**
         * @brief Broadcast a packet to all clients.
         * @param packet the packet.
         * @param idToIgnore the id to ignore. (-1 to ignore no one)
         * @throws sa::ex::IOContextDeadException if the ioContext is dead.
         */
        void broadcast(const std::unique_ptr<AbstractPacket> &packet, int idToIgnore) override { AbstractServer::broadcast(packet, idToIgnore); }

        /**
         * @brief Broadcast a packet to all clients.
         * @param packet the packet.
         * @throws sa::ex::IOContextDeadException if the ioContext is dead.
         */
        void broadcast(AbstractPacket &packet) override { AbstractServer::broadcast(packet); }

        /**
         * @brief Broadcast a packet to all clients.
         * @param packet the packet.
         * @throws sa::ex::IOContextDeadException if the ioContext is dead.
         */
        void broadcast(const std::shared_ptr<AbstractPacket> &packet) override { AbstractServer::broadcast(packet); }

        /**
         * @brief Broadcast a packet to all clients.
         * @param packet the packet.
         * @throws sa::ex::IOContextDeadException if the ioContext is dead.
         */
        void broadcast(const std::unique_ptr<AbstractPacket> &packet) override { AbstractServer::broadcast(packet); }

        /**
         * @brief Send a buffer to a client.
         * @param id the id of the client
         * @param buffer the buffer.
         * @throws sa::ex::IOContextDeadException if the ioContext is dead.
         * @deprecated use sendTo(int, AbstractPacket &) instead.
         */
        void sendTo(int id, ByteBuffer &buffer) override;

        /**
         * @brief Send a packet to a client.
         * @param id the id of the client
         * @param packet the packet.
         * @throws sa::PacketRegistry::PacketNotRegisteredException if the packet is not registered.
         * @throws sa::ex::IOContextDeadException if the ioContext is dead.
         */
        void sendTo(int id, AbstractPacket &packet) override { AbstractServer::sendTo(id, packet); }

        /**
         * @brief Send a packet to a client.
         * @param id the id of the client
         * @param packet the packet.
         * @throws sa::PacketRegistry::PacketNotRegisteredException if the packet is not registered.
         * @throws sa::ex::IOContextDeadException if the ioContext is dead.
         */
        void sendTo(int id, const std::shared_ptr<AbstractPacket> &packet) override { AbstractServer::sendTo(id, packet); }

        /**
         * @brief Send a packet to a client.
         * @param id the id of the client
         * @param packet the packet.
         * @throws sa::PacketRegistry::PacketNotRegisteredException if the packet is not registered.
         * @throws sa::ex::IOContextDeadException if the ioContext is dead.
         */
        void sendTo(int id, const std::unique_ptr<AbstractPacket> &packet) override { AbstractServer::sendTo(id, packet); }

        /**
         * @brief Disconnect a client.
         * @param id the id of the client.
         */
        void disconnect(int id) override;

        /**
         * @brief Disconnect a client.
         * @param id the id of the client.
         * @param reason the reason.
         */
        void disconnect(int id, const std::string &reason) override;

        /**
         * @brief Disconnect all clients.
         */
        void disconnectAll() override;

    protected:
        /**
         * @brief Called when a client is disconnected.
         * @param client the client.
         */
        void clientDisconnected(const std::shared_ptr<UDPConnectionToClient> &client);

    private:
        boost::asio::io_context _ioContext; /**< The asio io context */
        boost::asio::executor_work_guard<boost::asio::io_context::executor_type> _workGuard; /**< The asio work guard, to force the idle of ioContext */
        boost::asio::ip::udp::socket _socket; /**< The asio udp socket */
        boost::asio::ip::udp::endpoint _remoteEndpoint; /**< The remote endpoint */
        bool _asyncRun; /**< If the server is running asynchronously */
        std::thread _runThread; /**< The thread for the asynchronous run */

        /**
         * @brief Instanciate the server
         * @param packetRegistry the packet registry.
         * @param host the host.
         * @param port the port.
         */
        explicit UDPServer(const std::shared_ptr<PacketRegistry> &packetRegistry, const std::string &host = "0.0.0.0", uint16_t port = 2409);

        /**
         * @brief Asynchronously read to detect new client
         */
        void asyncRead();

        /**
         * @brief Get the client id from the endpoint.
         * @param endpoint the endpoint.
         * @return -1 if the client is not found.
         */
        int getClientId(boost::asio::ip::udp::endpoint &endpoint);

        /**
         * @brief Handle the packet data.
         * @param client the client.
         * @param packetId the packet id.
         * @param buffer the buffer.
         */
        void handlePacketData(const std::shared_ptr<ConnectionToClient> &client, uint16_t packetId, ByteBuffer &buffer);
    };
} // namespace sa

#endif // SATURNITY_UDPSERVER_HPP
