/*
** EPITECH PROJECT, 2023
** ConnectionToServer.hpp
** File description:
** ConnectionToServer.hpp
*/

#ifndef SATURNITY_CONNECTIONTOSERVER_HPP
#define SATURNITY_CONNECTIONTOSERVER_HPP

#include "AbstractConnection.hpp"

/**
 * @brief The Saturnity namespace.
 */
namespace sa {
    class AbstractClient; /**< Forward declaration. */

    /**
     * @brief The class for a connection to a server.
     */
    class ConnectionToServer : public AbstractConnection {
    public:
        /**
         * @brief Construct a new Connection To Server object. (Used by the client when receiving a packet from the server).
         * @param packetRegistry the packet registry.
         * @param client the client.
         */
        explicit ConnectionToServer(const std::shared_ptr<PacketRegistry> &packetRegistry, const std::shared_ptr<AbstractClient> &client);

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
         * @brief Disconnect from the server.
         * @param reason the reason.
         */
        inline void disconnect(const std::string &reason) override;

        /**
         * @brief Send a byte buffer to the server.
         * @param buffer the byte buffer.
         * @deprecated Use send(AbstractPacket &packet) instead.
         */
        inline void send(ByteBuffer &buffer) override;

        /**
         * @brief Send a packet to the server.
         * @param packet the packet.
         */
        inline void send(AbstractPacket &packet) override;

    private:
        std::shared_ptr<AbstractClient> _client; /**< The client. */
    };
} // namespace sa

/**
 * @brief ConnectionToServer as a shared pointer.
 */
using ConnectionToServerPtr = std::shared_ptr<sa::ConnectionToServer>;

#endif // SATURNITY_CONNECTIONTOSERVER_HPP
