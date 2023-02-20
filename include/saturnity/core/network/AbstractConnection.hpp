/*
** EPITECH PROJECT, 2023
** AbstractConnection.hpp
** File description:
** AbstractConnection.hpp
*/

#ifndef SATURNITY_ABSTRACTCONNECTION_HPP
#define SATURNITY_ABSTRACTCONNECTION_HPP

#include "saturnity/core/packet/AbstractPacket.hpp"
#include "saturnity/core/packet/PacketRegistry.hpp"

/**
 * @brief The Saturnity namespace.
 */
namespace sa {
    /**
     * @brief A connection between a client/server or server/client.
     */
    class AbstractConnection {
    public:
        /**
         * @brief Construct a new Connection object.
         * @param packetRegistry The packet registry.
         */
        explicit AbstractConnection(const std::shared_ptr<PacketRegistry> &packetRegistry) : _packetRegistry(packetRegistry) {}

        /**
         * @brief Destroy the Connection object.
         */
        virtual ~AbstractConnection() = default;

        /**
         * @brief Get the Id of the connection.
         * @return The Id of the connection.
         */
        virtual int getId() const = 0;

        /**
         * @brief Disconnect the connection.
         */
        virtual void disconnect() = 0;

        /**
         * @brief Disconnect the connection with a reason.
         * @param reason the reason.
         */
        virtual void disconnect(const std::string &reason) = 0;

        /**
         * @brief Send a packet to the connection.
         * @param packet the packet to send.
         * @throws sa::PacketRegistry::PacketNotRegisteredException if the packet is not registered.
         */
        virtual void send(AbstractPacket &packet) = 0;

        /**
         * @brief Send a packet to the connection.
         * @param packet the packet to send.
         * @throws sa::PacketRegistry::PacketNotRegisteredException if the packet is not registered.
         */
        virtual void send(const std::shared_ptr<AbstractPacket> &packet) { send(*packet); }

        /**
         * @brief Send a packet to the connection.
         * @param packet the packet to send.
         * @throws sa::PacketRegistry::PacketNotRegisteredException if the packet is not registered.
         */
        virtual void send(const std::unique_ptr<AbstractPacket> &packet) { send(*packet); }

    protected:
        /**
         * @brief Send a byte buffer to the connection. (Mostly used for packets and never used raw.)
         * @param buffer the byte buffer to send.
         * @deprecated Use send(AbstractPacket &packet) instead.
         */
        virtual void send(ByteBuffer &buffer) = 0;

    private:
        std::shared_ptr<PacketRegistry> _packetRegistry; /**< The packet registry. */
    };
} // namespace sa

#endif // SATURNITY_ABSTRACTCONNECTION_HPP
