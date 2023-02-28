/*
** EPITECH PROJECT, 2023
** AbstractUDPProtocol.hpp
** File description:
** AbstractUDPProtocol.hpp
*/

#ifndef SATURNITY_ABSTRACTUDPPROTOCOL_HPP
#define SATURNITY_ABSTRACTUDPPROTOCOL_HPP

/**
 * @brief The saturnity namespace.
 */
namespace sa {
    /**
     * @brief Abstract class just for setting the max buffer size.
     */
    class AbstractUDPProtocol {
    public:
        /**
         * @brief Instantiate a new AbstractUDPProtocol object.
         * @param maxBufferSize the max buffer size.
         */
        explicit AbstractUDPProtocol(int maxBufferSize = 1024) : maxBufferSize(maxBufferSize) {};

        /**
         * @brief Destroy the AbstractUDPProtocol object.
         */
        virtual ~AbstractUDPProtocol() = default;

        /**
         * @brief Get the max buffer size.
         * @return the max buffer size.
         */
        inline int getMaxBufferSize() const { return maxBufferSize; }

        /**
         * @brief Set the max buffer size.
         * @param bufferSize the new max buffer size.
         */
        inline void setMaxBufferSize(int bufferSize) { this->maxBufferSize = bufferSize; }

    protected:
        int maxBufferSize; /**< The max buffer size. */
    };
} // namespace sa

#endif // SATURNITY_ABSTRACTUDPPROTOCOL_HPP
