/*
** EPITECH PROJECT, 2023
** Core.hpp
** File description:
** Core.hpp
*/

#ifndef SATURNITY_CORE_HPP
#define SATURNITY_CORE_HPP

/**
 * @brief The Core header of Saturnity
 * @file Saturnity.hpp
 */

#include <cstdint>
#include <string>
#include <exception>

#ifndef SA_BUFFER_SIZE
/**
 * @brief The default size for the ByteBuffer
 */
#define SA_BUFFER_SIZE 4096 // NOLINT
#endif

using byte_t = std::uint8_t; // NOLINT

/**
 * @brief The Saturnity namespace.
 */
namespace sa {
    /**
     * @brief The base exception class for Saturnity
     */
    class Exception : public std::exception {
    public:
        /**
         * @brief Construct a simple exception with a message
         * @param message the message of the exception
         */
        explicit Exception(const std::string &message) : _msg(message) {}

        /**
         * @brief Get the message of the exception
         * @return an array of char
         */
        const char *what() const noexcept override
        {
            return this->_msg.c_str();
        }

    private:
        std::string _msg; /**< The message of the exception  */
    };
}

#define SA_EXCEPTION(name) class name : public sa::Exception { public: explicit name(const std::string &message) : sa::Exception(message) {} };

#endif // SATURNITY_CORE_HPP
