/*
** EPITECH PROJECT, 2023
** AbstractClient.hpp
** File description:
** AbstractClient.hpp
*/

#ifndef SATURNITY_ABSTRACTCLIENT_HPP
#define SATURNITY_ABSTRACTCLIENT_HPP

#include <memory>
#include <unordered_map>
#include "ConnectionToServer.hpp"
#include "saturnity/core/Core.hpp"
#include "saturnity/core/packet/PacketRegistry.hpp"
#include "saturnity/core/ThreadSafeQueue.hpp"
#include "saturnity/Exceptions.hpp"

/**
 * @brief The Saturnity namespace.
 */
namespace sa {
    /**
     * @brief The base class for a client.
     */
    class AbstractClient : public std::enable_shared_from_this<AbstractClient> {
    public:
        /**
         * @brief Thrown when the client is not connected to the server.
         */
        class ClientNotConnectedException : public sa::ex::Exception {
        public:
            /**
             * @brief Construct a new Client Not Connected Exception object.
             * @param message the message of the exception.
             */
            explicit ClientNotConnectedException(const std::string &message) : Exception(message) {}
        };

        /**
         * @brief Thrown when the client cannot connect to the server.
         */
        class ClientCannotConnectException : public sa::ex::Exception {
        public:
            /**
             * @brief Construct a new Client Not Connected Exception object.
             * @param message the message of the exception.
             */
            explicit ClientCannotConnectException(const std::string &message) : Exception(message) {}
        };

        enum EnumClientState {
            NONE, /**< The client is not initialized. */
            CONNECTED, /**< The client is connected to the server. */
            DISCONNECTED /**< The client is disconnected from the server. */
        };

        /**
         * @brief Construct a new Abstract Client object.
         * @param packetRegistry the packet registry.
         */
        explicit AbstractClient(const std::shared_ptr<PacketRegistry> &packetRegistry) : packetRegistry(packetRegistry), state(NONE), logger("Client") {};

        /**
         * @brief Destroy the Abstract Client object.
         */
        virtual ~AbstractClient() = default;

        /**
         * @brief Initialize the client.
         */
        virtual void init() = 0;

        /**
         * @brief Run the client. (May be blocking)
         */
        virtual void run() = 0;

        /**
         * @brief Connect to a server.
         * @param host the host.
         * @param port the port.
         * @throws std::out_of_range if the port is out of range.
         * @throws ClientCannotConnectException if the client cannot connect to the server.
         */
        virtual void connect(const std::string &host, uint16_t port) = 0;

        /**
         * @brief Disconnect from the server.
         */
        virtual void disconnect() = 0;

        /**
         * @brief Disconnect from the server.
         * @param forced true if the client is disconnected forcefully, false otherwise.
         */
        virtual void disconnect(bool forced) = 0;

        /**
         * @brief Check if the client is connected to the server.
         * @return true if the client is connected to the server, false otherwise.
         */
        bool isConnected() const { return this->state == EnumClientState::CONNECTED; }

        /**
         * @brief Send a byte buffer to the server.
         * @param buffer the byte buffer.
         * @deprecated Use send(AbstractPacket &packet) instead.
         */
        virtual void send(ByteBuffer &buffer) = 0;

        /**
         * @brief Send a packet to the server.
         * @param packet the packet.
         * @throws ClientNotConnectedException if the client is not connected to the server.
         * @throws sa::PacketRegistry::PacketNotRegisteredException if the packet is not registered
         */
        virtual void send(AbstractPacket &packet)
        {
            if (!this->isConnected()) throw ClientNotConnectedException("The client is not connected to the server.");
            ByteBuffer buffer;
            const uint16_t id = this->packetRegistry->getPacketId(packet);
            buffer.writeUShort(id);
            buffer.writeUShort(0);
            packet.toBytes(buffer);
            auto size = static_cast<uint16_t>(buffer.writerIndex());
            buffer.setWriterIndex(sizeof(uint16_t)); // Skip id, for rewrite size
            buffer.writeUShort(size - (sizeof(uint16_t) * 2)); // Write the packet body size
            buffer.setWriterIndex(size); // Restore writer index
            this->send(buffer);
        }

        /**
         * @brief Send a packet to the server.
         * @param packet the packet.
         * @throws ClientNotConnectedException if the client is not connected to the server.
         * @throws sa::PacketRegistry::PacketNotRegisteredException if the packet is not registered
         */
        virtual void send(const std::shared_ptr<AbstractPacket> &packet) { this->send(*packet); }

        /**
         * @brief Send a packet to the server.
         * @param packet the packet.
         * @throws ClientNotConnectedException if the client is not connected to the server.
         * @throws sa::PacketRegistry::PacketNotRegisteredException if the packet is not registered
         */
        virtual void send(const std::unique_ptr<AbstractPacket> &packet) { this->send(*packet); }

        /**
         * @brief Register a packet handler.
         * @tparam T the packet type.
         * @param handler the handler.
         * @throws ex::PacketHandlerAlreadyExistsException if a handler already exists for the packet.
         */
        template<typename T, typename = std::enable_if_t<std::is_base_of<AbstractPacket, T>::value, T>>
        void registerHandler(std::function<void(std::shared_ptr<ConnectionToServer> &server, T &packet)> handler)
        {
            const uint16_t id = this->packetRegistry->getPacketId<T>();
            if (this->packetHandlers.contains(id))
                throw ex::PacketHandlerAlreadyExistsException(spdlog::fmt_lib::format("A handler already exists for packet id: {}", id));

            this->packetHandlers[id] = [handler](std::shared_ptr<ConnectionToServer> &server, ByteBuffer &buffer) {
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
         * @brief Get the client state.
         * @return the client state.
         */
        EnumClientState getState() const { return this->state; }

        /**
         * @brief Get the client logger.
         * @return the client logger.
         */
        const spdlog::logger &getLogger() const { return this->logger; }

        /**
         * @brief Set the client logger.
         * @param log the client logger.
         */
        void setLogger(const spdlog::logger &log) { this->logger = log; }

        std::function<void(ConnectionToServerPtr &server)> onClientConnected; /**< The on client connected callback. */
        /**
         * @brief The on client disconnected callback.
         * @param server the server.
         * @param forced true if the client was disconnected by the server or when an error is thrown on read/write, false otherwise.
         */
        std::function<void(ConnectionToServerPtr &server, bool forced)> onClientDisconnected;
        /**
         * @brief The on client data received callback.
         * Will be called when the client receives the packet header & body
         * @param server the server connection.
         * @param packetId the packet id.
         * @param packetSize the packet size.
         * @param buffer the packet buffer.
         */
        std::function<void(ConnectionToServerPtr &server, std::uint16_t packetId, std::uint16_t packetSize, ByteBuffer &buffer)> onClientDataReceived;
        std::function<void(ConnectionToServerPtr &server, ByteBuffer &buffer)> onClientDataSent; /**< The on client data sent callback. */

    protected:
        std::shared_ptr<PacketRegistry> packetRegistry; /**< The packet registry. */
        std::shared_ptr<ConnectionToServer> connection; /**< The connection to the server. */
        std::unordered_map<uint16_t, std::function<void(ConnectionToServerPtr &server, ByteBuffer &buffer)>> packetHandlers; /**< The packet handlers. */
        EnumClientState state; /**< The client state. */
        spdlog::logger logger; /**< The logger. */
    };
} // namespace sa

#endif // SATURNITY_ABSTRACTCLIENT_HPP
