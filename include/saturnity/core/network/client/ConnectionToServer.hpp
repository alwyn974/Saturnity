/*
** EPITECH PROJECT, 2023
** ConnectionToServer.hpp
** File description:
** ConnectionToServer.hpp
*/

#ifndef SATURNITY_CONNECTIONTOSERVER_HPP
#define SATURNITY_CONNECTIONTOSERVER_HPP

#include "saturnity/core/network/AbstractConnection.hpp"

/**
 * @brief The Saturnity namespace.
 */
namespace sa {
    class AbstractClient;

    /**
     * @brief Class representing a connection to a server.
     */
    class ConnectionToServer : public AbstractConnection {
    public:
        /**
         * @brief Construct a new Connection To Server object. (Used by the client when receiving a packet from the server).
         * @param packetRegistry the packet registry.
         * @param client the client.
         * @param ip the ip of the server.
         * @param port the port of the server.
         */
        explicit ConnectionToServer(const std::shared_ptr<PacketRegistry> &packetRegistry, const std::shared_ptr<AbstractClient> &client, const std::string &ip, std::uint16_t port);

        /**
         * @brief Get the id of the connection.
         * @return 0 (always 0 for a connection to a server).
         */
        int getId() const override { return 0; }

        /**
         * @brief Disconnect from the server.
         */
        inline void disconnect() override;

        /**
         * @brief Send a byte buffer to the server.
         * @param buffer the byte buffer.
         * @deprecated Use send(AbstractPacket &packet) instead.
         */
        inline void send(ByteBuffer &buffer) override;

        /**
         * @brief Send a packet to the server.
         * @param packet the packet to send.
         * @throws sa::PacketRegistry::PacketNotRegisteredException if the packet is not registered.
         */
        inline void send(AbstractPacket &packet) override;

        /**
         * @brief Send a packet to the server.
         * @param packet the packet to send.
         * @throws sa::PacketRegistry::PacketNotRegisteredException if the packet is not registered.
         */
        void send(const std::shared_ptr<AbstractPacket> &packet) override;

        /**
         * @brief Send a packet to the server.
         * @param packet the packet to send.
         * @throws sa::PacketRegistry::PacketNotRegisteredException if the packet is not registered.
         */
        void send(const std::unique_ptr<AbstractPacket> &packet) override;

    private:
        std::shared_ptr<AbstractClient> _client; /**< The client. */
    };
} // namespace sa

/**
 * @brief ConnectionToServer as a shared pointer.
 */
using ConnectionToServerPtr = std::shared_ptr<sa::ConnectionToServer>;

#endif // SATURNITY_CONNECTIONTOSERVER_HPP
