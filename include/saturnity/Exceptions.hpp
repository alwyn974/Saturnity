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
 * @brief The Saturnity exception namespace.
 */
namespace sa::ex {
    /**
     * @brief Thrown when a packet handler already exists.
     */
    class PacketHandlerAlreadyExistsException : public sa::ex::Exception {
    public:
        /**
         * @brief Construct a new Packet Handler Already Exists Exception object.
         * @param message the message.
         */
        explicit PacketHandlerAlreadyExistsException(const std::string &message) : sa::ex::Exception(message) {};
    };

    /**
     * @brief Thrown when a packet handler is missing.
     */
    class PacketHandlerMissingException : public sa::ex::Exception {
    public:
        /**
         * @brief Construct a new Packet Handler Missing Exception object.
         * @param message the message.
         */
        explicit PacketHandlerMissingException(const std::string &message) : Exception(message) {};
    };

    /**
     * @brief Thrown when the ioContext used is dead.
     */
    class IOContextDeadException : public sa::ex::Exception {
    public:
        /**
         * @brief Construct a new IO Context Dead Exception object.
         * @param message the message.
         */
        explicit IOContextDeadException(const std::string &message) : Exception(message) {};
    };

    /**
     * @brief Thrown when a callback is not set.
     */
    class CallbackNotSetException : public sa::ex::Exception {
    public:
        /**
         * @brief Construct a new Callback Not Set Exception object.
         * @param message the message.
         */
        explicit CallbackNotSetException(const std::string &message) : Exception(message) {};
    };

    /**
     * @brief Thrown when the client is already running.
     */
    class AlreadyRunningException : public sa::ex::Exception {
    public:
        /**
         * @brief Construct a new Already Running Exception object.
         * @param message the message.
         */
        explicit AlreadyRunningException(const std::string &message) : Exception(message) {};
    };

} // namespace sa::ex

#endif // SATURNITY_EXCEPTIONS_HPP
