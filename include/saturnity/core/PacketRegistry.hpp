/*
** EPITECH PROJECT, 2023
** PacketRegistry.hpp
** File description:
** PacketRegistry.hpp
*/

#ifndef SATURNITY_PACKETREGISTRY_HPP
#define SATURNITY_PACKETREGISTRY_HPP

#include <functional>
#include <typeindex>
#include <unordered_map>
#include "AbstractPacket.hpp"

/**
 * @brief The namespace of the Saturnity library
 */
namespace sa {
    /**
     * @brief A registry that stores packets, their ids and their factories
     * @code
     * sa::PacketRegistry registry;
     * registry.registerPacket<HelloPacket>(0x1);
     * registry.registerPacket<WorldPacket>(0x2);
     *
     * // Check if a packet is registered
     * registry.hasPacket<HelloPacket>(); // true
     * WorldPacket worldPacket;
     * registry.hasPacket(worldPacket); // true
     * registry.hasPacket(0x01); // true
     *
     * // Get the id of a packet
     * registry.getPacketId<HelloPacket>(); // 0x1
     * registry.getPacketId(worldPacket); // 0x2
     *
     * // Create a packet from an id and a buffer
     * sa::ByteBuffer buffer;
     * std::unique_ptr<sa::AbstractPacket> helloPacket = registry.createPacket(0x1, buffer);
     * std::unique_ptr<sa::AbstractPacket> worldPacket = registry.createPacket(0x2, buffer);
     * @endcode
     */
    class PacketRegistry {
    public:
        /**
         * @brief Thrown when a packet is not registered
         */
        class PacketNotRegisteredException : public Exception {
        public:
            /**
             * @brief Construct a new Packet Not Registered Exception object
             * @param message the message
             */
            explicit PacketNotRegisteredException(const std::string &message) : Exception(message) {}
        };

        /**
         * @brief Thrown when a packet is already registered
         */
        class PacketAlreadyRegisteredException : public Exception {
        public:
            /**
             * @brief Construct a new Packet Already Registered Exception object
             * @param message the message
             */
            explicit PacketAlreadyRegisteredException(const std::string &message) : Exception(message) {}
        };

        /**
         * @brief Thrown when a packet is missing an empty constructor
         */
        class PacketMissingEmptyConstructorException : public Exception {
        public:
            /**
             * @brief Construct a new Packet Missing Empty Constructor Exception object
             * @param message the message
             */
            explicit PacketMissingEmptyConstructorException(const std::string &message) : Exception(message) {}
        };

        /**
         * @brief A function that creates a packet from a buffer
         */
        using PacketFactory = std::function<std::unique_ptr<AbstractPacket>(ByteBuffer &buffer)>;

        /**
         * @brief Register a packet
         * @tparam T type of the packet (must inherit from AbstractPacket)
         * @param id the id of the packet
         * @throws PacketAlreadyRegisteredException if the packet is already registered
         * @throws PacketMissingEmptyConstructorException if the packet is missing an empty constructor
         */
        template<typename T, typename = std::enable_if_t<std::is_base_of<AbstractPacket, T>::value, T>>
        void registerPacket(std::uint16_t id)
        {
            if (!std::is_default_constructible<T>())
                throw PacketMissingEmptyConstructorException(spdlog::fmt_lib::format("Packet: {} is missing an empty constructor", typeid(T).name()));
            if (this->_packetFactories.contains(id))
                throw PacketAlreadyRegisteredException(spdlog::fmt_lib::format("Packet with id: {} is already registered", id));
            auto typeIndex = std::type_index(typeid(T)); // NOLINT
            if (this->_packetRegistry.contains(typeIndex))
                throw PacketAlreadyRegisteredException(spdlog::fmt_lib::format("Packet with type: {} is already registered", typeIndex.name()));
            this->_packetRegistry[typeIndex] = id;
            this->_packetFactories[id] = [](ByteBuffer &buffer) {
                std::unique_ptr<AbstractPacket> packet = std::make_unique<T>();
                packet->fromBytes(buffer);
                return packet;
            };
        }

        /**
         * @brief Get the packet id
         * @tparam T type of the packet (must inherit from AbstractPacket)
         * @return the id of the packet
         * @throws PacketNotRegisteredException if the packet is not registered
         */
        template<typename T, typename = std::enable_if_t<std::is_base_of<AbstractPacket, T>::value, T>>
        std::uint16_t getPacketId()
        {
            auto typeIndex = std::type_index(typeid(T)); // NOLINT
            if (!this->_packetRegistry.contains(typeIndex))
                throw PacketNotRegisteredException(spdlog::fmt_lib::format("Packet with type: {} is not registered", typeIndex.name()));
            return this->_packetRegistry[typeIndex];
        }

        /**
         * @brief Get the packet id
         * @param packet the packet
         * @return the id of the packet
         * @throws PacketNotRegisteredException if the packet is not registered
         */
        std::uint16_t getPacketId(AbstractPacket &packet);

        /**
         * @brief Create a packet from a buffer
         * @param id the id of the packet
         * @param buffer the buffer
         * @return the packet
         * @throws PacketNotRegisteredException if the packet is not registered
         */
        std::unique_ptr<AbstractPacket> createPacket(std::uint16_t id, ByteBuffer &buffer);

        /**
         * @brief Create a packet from a buffer
         * @tparam T type of the packet (must inherit from AbstractPacket)
         * @param buffer the buffer
         * @return the packet
         * @throws PacketNotRegisteredException if the packet is not registered
         */
        template<typename T, typename = std::enable_if_t<std::is_base_of<AbstractPacket, T>::value, T>>
        std::unique_ptr<T> createPacket(ByteBuffer &buffer)
        {
            auto packet = this->createPacket(this->getPacketId<T>(), buffer);
            return std::unique_ptr<T>(static_cast<T *>(packet.release()));
        }

        /**
         * @brief Check if a packet is registered
         * @param id the id of the packet
         * @return true if the packet is registered, false otherwise
         */
        bool hasPacket(std::uint16_t id);

        /**
         * @brief Check if a packet is registered
         * @param packet the packet
         * @return true if the packet is registered, false otherwise
         */
        bool hasPacket(AbstractPacket &packet);

        /**
         * @brief Check if a packet is registered
         * @tparam T type of the packet (must inherit from AbstractPacket)
         * @return true if the packet is registered, false otherwise
         */
        template<typename T, typename = std::enable_if_t<std::is_base_of<AbstractPacket, T>::value, T>>
        bool hasPacket()
        {
            auto typeIndex = std::type_index(typeid(T)); // NOLINT
            return this->_packetRegistry.contains(typeIndex);
        }

        /**
         * @brief Get the Packet Registry, map containing the packet type and the packet id
         * @return the packet registry
         */
        const std::unordered_map<std::type_index, std::uint16_t> &getPacketEntries() const;

        /**
         * @brief Get the Packet Factories, map containing the packet id and the packet factory
         * @return the packet factories
         */
        const std::unordered_map<std::uint16_t, PacketFactory> &getPacketFactories() const;

        /**
         * @brief Get the instance of the packet registry
         * @return the instance of the packet registry
         */
        static std::unique_ptr<PacketRegistry> &getInstance();

    private:
        std::unordered_map<std::type_index, std::uint16_t> _packetRegistry; /**< Registry containing all packets */
        std::unordered_map<std::uint16_t, PacketFactory> _packetFactories; /**< Factory containing the packet creator, used when receiving a packet */

        static std::unique_ptr<PacketRegistry> instance; /**< The instance of the packet registry */
    };
} // namespace sa

#endif // SATURNITY_PACKETREGISTRY_HPP
