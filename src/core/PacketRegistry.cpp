/*
** EPITECH PROJECT, 2023
** PacketRegistry.cpp
** File description:
** PacketRegistry.cpp
*/

#include "saturnity/core/PacketRegistry.hpp"

namespace sa {

    std::unique_ptr<PacketRegistry> PacketRegistry::instance = nullptr;

    std::unique_ptr<PacketRegistry> &PacketRegistry::getInstance()
    {
        if (PacketRegistry::instance == nullptr) PacketRegistry::instance = std::make_unique<PacketRegistry>();
        return instance;
    }

    std::uint16_t PacketRegistry::getPacketId(AbstractPacket &packet)
    {
        auto typeIndex = std::type_index(typeid(packet));
        if (!this->_packetRegistry.contains(typeIndex))
            throw PacketNotRegisteredException(spdlog::fmt_lib::format("Packet with type: {} is not registered", typeIndex.name()));
        return this->_packetRegistry[typeIndex];
    }

    std::unique_ptr<sa::AbstractPacket> PacketRegistry::createPacket(std::uint16_t id, ByteBuffer &buffer)
    {
        if (!this->_packetFactories.contains(id)) throw PacketNotRegisteredException(spdlog::fmt_lib::format("Packet with id: {} is not registered", id));
        return this->_packetFactories[id](buffer);
    }

    bool PacketRegistry::hasPacket(std::uint16_t id)
    {
        return this->_packetFactories.contains(id);
    }

    bool sa::PacketRegistry::hasPacket(AbstractPacket &packet)
    {
        auto typeIndex = std::type_index(typeid(packet));
        return this->_packetRegistry.contains(typeIndex);
    }

    const std::unordered_map<std::type_index, std::uint16_t> &PacketRegistry::getPacketEntries() const
    {
        return _packetRegistry;
    }

    const std::unordered_map<std::uint16_t, PacketRegistry::PacketFactory> &PacketRegistry::getPacketFactories() const
    {
        return _packetFactories;
    }
} // namespace sa
