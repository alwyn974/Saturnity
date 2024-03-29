/*
** EPITECH PROJECT, 2023
** AbstractServer.hpp
** File description:
** AbstractServer.hpp
*/

#ifndef SATURNITY_ABSTRACTSERVER_HPP
#define SATURNITY_ABSTRACTSERVER_HPP

#include "ConnectionToClient.hpp"
#include "saturnity/core/Core.hpp"
#include "saturnity/core/packet/PacketRegistry.hpp"
#include "saturnity/core/ThreadSafeQueue.hpp"
#include "saturnity/Exceptions.hpp"

/**
 * @brief The Saturnity namespace.
 */
namespace sa {
    /**
     * @brief The base class for a server.
     */
    class AbstractServer : public std::enable_shared_from_this<AbstractServer> {
    public:
        /**
         * @brief Construct a new Abstract Server object.
         * @param packetRegistry the packet registry.
         * @param host the host. (default 0.0.0.0)
         * @param port the port. (default 2409)
         */
        explicit AbstractServer(const std::shared_ptr<PacketRegistry> &packetRegistry, const std::string &host = "0.0.0.0", uint16_t port = 2409) :
            packetRegistry(packetRegistry),
            host(host),
            port(port),
            logger("Server"),
            running(false),
            nextId(0) {};

        /**
         * @brief Destroy the Abstract Server object.
         */
        virtual ~AbstractServer() = default;

        /**
         * @brief Initialize the server.
         * @throws sa::ex::CallbackNotSetException if some callbacks are not set.
         */
        virtual void init() = 0;

        /**
         * @brief Run the server.
         */
        virtual void run() = 0;

        /**
         * @brief Start the server.
         */
        virtual void start() = 0;

        /**
         * @brief Stop the server.
         */
        virtual void stop() = 0;

        /**
         * @brief Send a packet to all clients.
         * @param packet sthe packet.
         * @param idToIgnore the client id to ignore. (-1 to ignore no one)
         * @throws sa::PacketRegistry::PacketNotRegisteredException if the packet is not registered
         */
        virtual void broadcast(AbstractPacket &packet, int idToIgnore) = 0;

        /**
         * @brief Send a packet to all clients.
         * @param packet the packet.
         * @param idToIgnore the client id to ignore. (-1 to ignore no one)
         * @throws sa::PacketRegistry::PacketNotRegisteredException if the packet is not registered
         */
        virtual void broadcast(const std::shared_ptr<AbstractPacket> &packet, int idToIgnore) { this->broadcast(*packet, idToIgnore); }

        /**
         * @brief Send a packet to all clients.
         * @param packet the packet.
         * @param idToIgnore the client id to ignore. (-1 to ignore no one)
         * @throws sa::PacketRegistry::PacketNotRegisteredException if the packet is not registered
         */
        virtual void broadcast(const std::unique_ptr<AbstractPacket> &packet, int idToIgnore) { this->broadcast(*packet, idToIgnore); }

        /**
         * @brief Send a packet to all clients.
         * @param packet the packet.
         * @throws sa::PacketRegistry::PacketNotRegisteredException if the packet is not registered
         */
        virtual void broadcast(AbstractPacket &packet) { this->broadcast(packet, -1); }

        /**
         * @brief Send a packet to all clients.
         * @param packet the packet.
         * @throws sa::PacketRegistry::PacketNotRegisteredException if the packet is not registered
         */
        virtual void broadcast(const std::shared_ptr<AbstractPacket> &packet) { this->broadcast(*packet); }

        /**
         * @brief Send a packet to all clients.
         * @param packet the packet.
         * @throws sa::PacketRegistry::PacketNotRegisteredException if the packet is not registered
         */
        virtual void broadcast(const std::unique_ptr<AbstractPacket> &packet) { this->broadcast(*packet); }

        /**
         * @brief Send a byte buffer to a client.
         * @param id the client id.
         * @param buffer the byte buffer.
         * @deprecated use sendTo(int id, AbstractPacket &packet) instead.
         */
        virtual void sendTo(int id, ByteBuffer &buffer) = 0;

        /**
         * @brief Send a packet to a client.
         * @param id the client id.
         * @param packet the packet.
         * @throws sa::PacketRegistry::PacketNotRegisteredException if the packet is not registered
         */
        virtual void sendTo(int id, AbstractPacket &packet)
        {
            ByteBuffer buffer;
            const uint16_t packetId = this->packetRegistry->getPacketId(packet);
            buffer.writeUShort(packetId);
            buffer.writeUShort(0);
            packet.toBytes(buffer);
            auto size = static_cast<uint16_t>(buffer.writerIndex());
            buffer.setWriterIndex(sizeof(uint16_t)); // Skip id, for rewrite size
            buffer.writeUShort(size - (sizeof(uint16_t) * 2)); // Write the packet body size
            buffer.setWriterIndex(size); // Restore writer index
            this->sendTo(id, buffer);
        }

        /**
         * @brief Send a packet to a client.
         * @param id the client id.
         * @param packet the packet.
         * @throws sa::PacketRegistry::PacketNotRegisteredException if the packet is not registered
         */
        virtual void sendTo(int id, const std::shared_ptr<AbstractPacket> &packet) { this->sendTo(id, *packet); }

        /**
         * @brief Send a packet to a client.
         * @param id the client id.
         * @param packet the packet.
         * @throws sa::PacketRegistry::PacketNotRegisteredException if the packet is not registered
         */
        virtual void sendTo(int id, const std::unique_ptr<AbstractPacket> &packet) { this->sendTo(id, *packet); }

        /**
         * @brief Register a packet handler.
         * @tparam T the packet type.
         * @param handler the handler.
         * @throws ex::PacketHandlerAlreadyExistsException if a handler already exists for the packet.
         */
        template<typename T, typename = std::enable_if_t<std::is_base_of<AbstractPacket, T>::value, T>>
        void registerHandler(std::function<void(std::shared_ptr<ConnectionToClient> &server, T &packet)> handler)
        {
            const uint16_t id = this->packetRegistry->getPacketId<T>();
            if (this->packetHandlers.contains(id))
                throw ex::PacketHandlerAlreadyExistsException(spdlog::fmt_lib::format("A handler already exists for packet id: {}", id));

            this->packetHandlers[id] = [handler](std::shared_ptr<ConnectionToClient> &server, ByteBuffer &buffer) {
                T packet;
                packet.fromBytes(buffer);
                handler(server, packet);
            };
        }

        /**
         * @brief Unregister a packet handler.
         * @tparam T the packet type.
         * @throws ex::PacketHandlerMissingException if no handler exists for the packet.
         */
        template<typename T, typename = std::enable_if_t<std::is_base_of<AbstractPacket, T>::value, T>>
        void unregisterHandler()
        {
            const uint16_t id = this->packetRegistry->getPacketId<T>();
            if (!this->packetHandlers.contains(id)) throw ex::PacketHandlerMissingException(spdlog::fmt_lib::format("No handler exists for packet id: {}", id));
            this->packetHandlers.erase(id);
        }

        /**
         * @brief Disconnect a client.
         * @param id the client id.
         */
        virtual void disconnect(int id) = 0;

        /**
         * @brief Disconnect a client with a reason.
         * @param id the client id.
         * @param reason the reason.
         */
        virtual void disconnect(int id, const std::string &reason) = 0;

        /**
         * @brief Disconnect all clients.
         */
        virtual void disconnectAll() = 0;

        /**
         * @brief Get the server host.
         * @return the host.
         */
        const std::string &getHost() const { return host; }

        /**
         * @brief Get the server port.
         * @return the port.
         */
        uint16_t getPort() const { return port; }

        /**
         * @brief Get the server logger.
         * @return the logger.
         */
        const spdlog::logger &getLogger() const { return logger; }

        /**
         * @brief Get the server logger.
         * @return the logger.
         */
        spdlog::logger &getLogger() { return logger; }

        /**
         * @brief Check if the server is running.
         * @return true if the server is running, false otherwise.
         */
        bool isRunning() const { return running; }

        /**
         * @brief The on client connect callback, this callback is used to accept or reject a client connection.
         * @param client the client.
         */
        std::function<bool(ConnectionToClientPtr &client)> onClientConnect;
        std::function<void(ConnectionToClientPtr &client)> onClientConnected; /**< The on client connected callback. */
        std::function<void(ConnectionToClientPtr &client)> onClientDisconnected; /**< The on client disconnected callback. */
        /**
         * @brief The on server data received callback.
         * Will be called when the server receives a packet header & body
         * @param client the client connection.
         * @param packetId the packet id.
         * @param packetSize the packet size.
         * @param buffer the packet buffer.
         */
        std::function<void(ConnectionToClientPtr &client, std::uint16_t packetId, std::uint16_t packetSize, ByteBuffer &buffer)> onServerDataReceived;
        std::function<void(ConnectionToClientPtr &client, ByteBuffer &buffer)> onServerDataSent; /**< The on server data sent callback. */

    protected:
        std::shared_ptr<PacketRegistry> packetRegistry; /**< The packet registry. */
        std::unordered_map<int, ConnectionToClientPtr> connections; /**< The connections to the clients */
        std::unordered_map<uint16_t, std::function<void(ConnectionToClientPtr &server, ByteBuffer &buffer)>> packetHandlers; /**< The packet handlers. */
        std::string host; /**< The host. */
        uint16_t port; /**< The port. */
        spdlog::logger logger; /**< The logger. */
        bool running; /**< The running state. */
        int nextId; /**< The next id. */
    };
} // namespace sa

#endif // SATURNITY_ABSTRACTSERVER_HPP
