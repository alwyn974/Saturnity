/*
** EPITECH PROJECT, 2023
** AbstractPacket.hpp
** File description:
** AbstractPacket.hpp
*/

#ifndef SATURNITY_ABSTRACT_PACKET_HPP
#define SATURNITY_ABSTRACT_PACKET_HPP

#include "saturnity/core/ByteBuffer.hpp"
#include "saturnity/core/Core.hpp"

/**
 * @brief The Saturnity namespace.
 */
namespace sa {
    /**
     * @brief A packet is a data structure that can be serialized and deserialized through bytes.
     * You can create a packet by inheriting from this class and implementing the toBytes and fromBytes methods.
     * Example:
     * @code
     * class HelloPacket : public sa::AbstractPacket {
     * public:
     *    HelloPacket() : sa::AbstractPacket(sa::AbstractPacket::EnumPacketType::UDP) {}; // This empty constructor is MANDATORY, the packet registry cannot
     * create a packet without it. explicit HelloPacket(const std::string &message) : sa::AbstractPacket(sa::AbstractPacket::EnumPacketType::UDP),
     * _message(message) {}; void toBytes(sa::ByteBuffer &byteBuffer) override { byteBuffer.writeString(this->_message);
     *    }
     *    void fromBytes(sa::ByteBuffer &byteBuffer) override {
     *         this->_message = byteBuffer.readString();
     *    }
     *
     *    std::string getMessage() const {
     *        return this->_message;
     *    }
     * @endcode
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
         * @brief Destroy the Abstract Packet object.
         */
        virtual ~AbstractPacket() = default;

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
