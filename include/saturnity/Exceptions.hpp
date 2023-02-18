/*
** EPITECH PROJECT, 2023
** Exceptions.hpp
** File description:
** Exceptions.hpp
*/

#ifndef SATURNITY_EXCEPTIONS_HPP
#define SATURNITY_EXCEPTIONS_HPP

#include "core/Core.hpp"

/**
 * @brief The Saturnity namespace.
 */
namespace sa {
    /**
     * @brief Thrown when a packet handler already exists.
     */
    class PacketHandlerAlreadyExistsException : public sa::Exception {
    public:
        /**
         * @brief Construct a new Packet Handler Already Exists Exception object.
         * @param message the message.
         */
        explicit PacketHandlerAlreadyExistsException(const std::string &message) : Exception(message) {};
    };

    /**
     * @brief Thrown when a packet handler is missing.
     */
    class PacketHandlerMissingException : public sa::Exception {
    public:
        /**
         * @brief Construct a new Packet Handler Missing Exception object.
         * @param message the message.
         */
        explicit PacketHandlerMissingException(const std::string &message) : Exception(message) {};
    };
} // namespace sa

#endif // SATURNITY_EXCEPTIONS_HPP
