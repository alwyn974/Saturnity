/*
** EPITECH PROJECT, 2023
** ConnectionToClient.hpp
** File description:
** ConnectionToClient.hpp
*/

#ifndef SATURNITY_CONNECTIONTOCLIENT_HPP
#define SATURNITY_CONNECTIONTOCLIENT_HPP

#include "saturnity/core/network/AbstractConnection.hpp"

/**
 * @brief The Saturnity namespace.
 */
namespace sa {
    class AbstractServer;

    /**
     * @brief Class representing a connection to a client.
     */
    class ConnectionToClient : public AbstractConnection {
    public:
        /**
         * @brief Construct a new Connection To Client object. (Used by the server).
         * @param packetRegistry the packet registry.
         * @param id the id of the connection.
         * @param server the server.
         * @param ip the ip of the client.
         * @param port the port of the client.
         */
        explicit ConnectionToClient(const std::shared_ptr<PacketRegistry> &packetRegistry, int id, const std::shared_ptr<AbstractServer> &server,
                                    const std::string &ip, std::uint16_t port);

        /**
         * @brief Start the connection.
         */
        virtual void start();

        /**
         * @brief Disconnect the client.
         */
        void disconnect() override;

        /**
         * @brief Disconnect the client with a reason.
         * @param reason the reason.
         */
        virtual void disconnect(const std::string &reason);

        /**
         * @brief Send a byte buffer to the client.
         * @param buffer the byte buffer.
         * @deprecated Use send(AbstractPacket &packet) instead.
         */
        void send(ByteBuffer &buffer) override;

        /**
         * @brief Send a packet to the client.
         * @param packet the packet.
         */
        void send(AbstractPacket &packet) override;

        /**
         * @brief Send a packet to the client.
         * @param packet the packet to send.
         * @throws sa::PacketRegistry::PacketNotRegisteredException if the packet is not registered.
         */
        void send(const std::shared_ptr<AbstractPacket> &packet) override;

        /**
         * @brief Send a packet to the client.
         * @param packet the packet to send.
         * @throws sa::PacketRegistry::PacketNotRegisteredException if the packet is not registered.
         */
        void send(const std::unique_ptr<AbstractPacket> &packet) override;

        /**
         * @brief Get the id of the connection.
         * @return the id of the connection.
         */
        int getId() const override;

        /**
         * @brief Check if the client is connected.
         * @return true if the client is connected.
         */
        bool isConnected() const;

        /**
         * @brief Set the id of the connection.
         * @param connectionId the id of the connection.
         */
        void setId(int connectionId);

    protected:
        int id; /**< The id of the connection. */
        std::shared_ptr<AbstractServer> server; /**< The server. */
        bool connected; /**< If the client is connected. */
    };
} // namespace sa

/**
 * @brief The connection to client pointer type.
 */
using ConnectionToClientPtr = std::shared_ptr<sa::ConnectionToClient>;

#endif // SATURNITY_CONNECTIONTOCLIENT_HPP
