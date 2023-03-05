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
         * @param ip The ip of the connection.
         * @param port The port of the connection.
         */
        explicit AbstractConnection(const std::shared_ptr<PacketRegistry> &packetRegistry, const std::string &ip, std::uint16_t port) :
            _packetRegistry(packetRegistry),
            _ip(ip),
            _port(port)
        {}

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

        /**
         * @brief Get the Ip of the connection.
         * @return the Ip of the connection.
         */
        const std::string &getIp() const { return this->_ip; }

        /**
         * @brief Set the Ip of the connection.
         * @param ip the new Ip of the connection.
         */
        void setIp(const std::string &ip) { this->_ip = ip; }

        /**
         * @brief Get the Port of the connection.
         * @return the Port of the connection.
         */
        uint16_t getPort() const { return this->_port; }

        /**
         * @brief Set the Port of the connection.
         * @param port the new Port of the connection.
         */
        void setPort(uint16_t port) { this->_port = port; }

    protected:
        /**
         * @brief Send a byte buffer to the connection. (Mostly used for packets and never used raw.)
         * @param buffer the byte buffer to send.
         * @deprecated Use send(AbstractPacket &packet) instead.
         */
        virtual void send(ByteBuffer &buffer) = 0;

        std::string _ip; /**< The ip of the connection. */
        std::uint16_t _port; /**< The port of the connection. */

    private:
        std::shared_ptr<PacketRegistry> _packetRegistry; /**< The packet registry. */
    };
} // namespace sa

#endif // SATURNITY_ABSTRACTCONNECTION_HPP
