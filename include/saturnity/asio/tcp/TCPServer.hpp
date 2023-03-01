/*
** EPITECH PROJECT, 2023
** TCPServer.hpp
** File description:
** TCPServer.hpp
*/

#ifndef SATURNITY_TCPSERVER_HPP
#define SATURNITY_TCPSERVER_HPP

#include "saturnity/core/network/server/AbstractServer.hpp"
#include "TCPConnectionToClient.hpp"
#include <spdlog/sinks/stdout_color_sinks.h>
#include <boost/asio.hpp>

/**
 * @brief TCP server implementation.
 */
namespace sa {
    /**
     * @brief TCP server implementation with boost::asio.
     * @throws sa::ex::IOContextDeadException if the ioContext is dead. (send & read)
     */
    class TCPServer : public AbstractServer {
    public:
        friend class TCPConnectionToClient;

        /**
         * @brief Create a new TCP server.
         * @param packetRegistry the packet registry.
         * @param host the host.
         * @param port the port.
         * @return the TCP server.
         */
        static std::shared_ptr<TCPServer> create(
            const std::shared_ptr<PacketRegistry> &packetRegistry, const std::string &host = "0.0.0.0", uint16_t port = 2409)
        {
            return std::shared_ptr<TCPServer>(new TCPServer(packetRegistry, host, port));
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
    private:
        boost::asio::io_context _ioContext; /**< The asio io context */
        boost::asio::executor_work_guard<boost::asio::io_context::executor_type> _workGuard; /**< The asio work guard, to force the idle of ioContext */
        boost::asio::ip::tcp::acceptor _acceptor; /**< The asio tcp acceptor */
        boost::asio::ip::tcp::socket _socket; /**< The asio tcp socket */
        bool _asyncRun; /**< If the server is running asynchronously */
        std::thread _runThread; /**< The thread for the asynchronous run */

        /**
         * @brief Instanciate the server
         * @param packetRegistry the packet registry.
         * @param host the host.
         * @param port the port.
         */
        explicit TCPServer(const std::shared_ptr<PacketRegistry> &packetRegistry, const std::string &host = "0.0.0.0", uint16_t port = 2409);

        /**
         * @brief Simply wait for a connection.
         */
        void waitForConnection();

    protected:
        /**
         * @brief Called when a client is disconnected.
         * @param client the client.
         */
        void clientDisconnected(const std::shared_ptr<TCPConnectionToClient> &client);

        /**
         * @brief Called when a client has sent a packet.
         * @param client the client.
         * @param packetId the packet id.
         * @param buffer the buffer.
         */
        void clientSentPacket(const std::shared_ptr<TCPConnectionToClient> &client, std::uint16_t packetId, ByteBuffer &buffer);
    };
} // namespace sa

#endif // SATURNITY_TCPSERVER_HPP
