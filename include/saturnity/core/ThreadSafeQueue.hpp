/*
** EPITECH PROJECT, 2023
** ThreadSafeQueue.hpp
** File description:
** ThreadSafeQueue.hpp
*/

#ifndef SATURNITY_THREADSAFEQUEUE_HPP
#define SATURNITY_THREADSAFEQUEUE_HPP

#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>

/**
 * @brief The Saturnity namespace.
 */
namespace sa {
    /**
     * @brief A thread-safe queue.
     * @tparam T the type of the queue.
     * @code
     * TSQueue<int> queue;
     * queue.push(1);
     * queue.push(2);
     *
     * int a = queue.waitPop();
     * int b = queue.waitPop();
     * @endcode
     */
    template<typename T>
    class TSQueue {
    public:
        /**
         * @brief Push an element to the queue. (Can be blocking)
         * @param element the element to push.
         */
        void push(T element)
        {
            std::unique_lock<std::mutex> lock(_mutex);
            _queue.push(element);
            lock.unlock();
            _condition.notify_one();
        }

        /**
         * @brief Wait for an element to be in the queue and pop it.
         * @return the element.
         */
        T waitPop()
        {
            std::unique_lock<std::mutex> lock(_mutex);
            _condition.wait(lock, [this] {
                return !_queue.empty();
            });
            T value = std::move(_queue.front());
            _queue.pop();
            return value;
        }

        /**
         * @brief Try to pop an element from the queue.
         * @param value the value to pop.
         * @return true if the element was popped, false if the queue is empty.
         */
        bool tryPop(T& value)
        {
            std::unique_lock<std::mutex> lock(_mutex);
            if (_queue.empty())
                return false;
            value = std::move(_queue.front());
            _queue.pop();
            return true;
        }

        /**
         * @brief Get the front element of the queue.
         * @return the front element of the queue.
         */
        T &front()
        {
            std::unique_lock<std::mutex> lock(_mutex);
            return _queue.front();
        }

        /**
         * @brief Pop an element from the queue.
         * @return true if the element was popped, false if the queue is empty.
         */
        bool pop()
        {
            std::unique_lock<std::mutex> lock(_mutex);
            if (_queue.empty())
                return false;
            _queue.pop();
            return true;
        }

        /**
         * @brief Check if the queue is empty.
         * @return true if the queue is empty, false otherwise.
         */
        bool empty()
        {
            std::unique_lock<std::mutex> lock(_mutex);
            return _queue.empty();
        }

        /**
         * @brief Get the size of the queue.
         * @return the size of the queue.
         */
        std::size_t size()
        {
            std::unique_lock<std::mutex> lock(_mutex);
            return _queue.size();
        }

        /**
         * @brief Clear the queue.
         */
        void clear()
        {
            std::unique_lock<std::mutex> lock(_mutex);
            std::queue<T> emptyQueue;
            std::swap(_queue, emptyQueue);
        }

        /**
         * @brief Get the queue.
         * @return the queue.
         */
        std::queue<T> getQueue()
        {
            std::unique_lock<std::mutex> lock(_mutex);
            return _queue;
        }

    private:
        std::queue<T> _queue; /**< The queue. */
        mutable std::mutex _mutex; /**< The mutex. */
        std::condition_variable _condition; /**< The condition variable. */
    };
} // namespace sa

#endif // SATURNITY_THREADSAFEQUEUE_HPP
