/*
** EPITECH PROJECT, 2023
** PacketWriter.hpp
** File description:
** PacketWriter.hpp
*/

#ifndef SATURNITY_PACKETWRITER_HPP
#define SATURNITY_PACKETWRITER_HPP

#include "Core.hpp"

/**
 * @brief The Saturnity namespace.
 */
namespace sa {
    /**
     * @brief A packet writer is a class that can write bytes into a buffer.
     */
    class PacketWriter {
    public:
        explicit PacketWriter(const std::size_t &bufferSize);

    private:
    };
}

#endif //SATURNITY_PACKETWRITER_HPP
