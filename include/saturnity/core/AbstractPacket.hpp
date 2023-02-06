/*
** EPITECH PROJECT, 2023
** AbstractPacket.hpp
** File description:
** AbstractPacket.hpp
*/

#ifndef SATURNITY_ABSTRACT_PACKET_HPP
#define SATURNITY_ABSTRACT_PACKET_HPP

#include "Core.hpp"
#include "ByteBuffer.hpp"

/**
 * @brief The Saturnity namespace.
 */
namespace sa {
    /**
     * @brief A packet is a data structure that can be serialized and deserialized through bytes.
     */
    class AbstractPacket {
    public:
        enum EnumPacketType {
            UDP = 0, /**< UDP packet */
            TCP = 1, /**< TCP packet */
        };

        /**
         * @brief Construct a new Abstract Packet object.
         * @param type the packet type.
         */
        explicit AbstractPacket(const EnumPacketType &type) : _type(type) {};

        /**
         * @brief Serialize the packet into bytes.
         * @param byteBuffer the byte buffer to serialize data into bytes
         */
        virtual void toBytes(ByteBuffer &byteBuffer) = 0;

        /**
         * @brief Deserialize the packet from bytes.
         * @param byteBuffer the byte buffer to deserialize data from bytes
         */
        virtual void fromBytes(ByteBuffer &byteBuffer) = 0;

        /**
         * @brief Check if the packet is a UDP packet.
         * @return true if the packet is a UDP packet, false otherwise.
         */
        inline bool isUDP() const { return this->_type == EnumPacketType::UDP; }

        /**
         * @brief Check if the packet is a TCP packet.
         * @return true if the packet is a TCP packet, false otherwise.
         */
        inline bool isTCP() const { return this->_type == EnumPacketType::TCP; }

        /**
         * @brief Get the packet type.
         * @return the packet type.
         */
        inline const EnumPacketType &getType() const { return this->_type; }

    private:
        EnumPacketType _type; /**< The packet type. */
    };
} // namespace sa

#endif // SATURNITY_ABSTRACT_PACKET_HPP
