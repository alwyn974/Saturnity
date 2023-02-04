/*
** EPITECH PROJECT, 2023
** Saturnity.hpp
** File description:
** Saturnity.hpp
*/

#ifndef SATURNITY_SATURNITY_HPP
#define SATURNITY_SATURNITY_HPP

#include <spdlog/spdlog.h>
#include <SFML/Graphics.hpp>

namespace sa {
    class Test {
    public:
        Test() = default;

        /**
         * @brief Test function
         */
        inline void test() const
        {
            spdlog::info("Test");

            sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
            sf::CircleShape shape(100.0);
            shape.setFillColor(sf::Color::Green);
            while (window.isOpen()) {
                sf::Event event = {};
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        window.close();
                }
                window.clear();
                window.draw(shape);
                window.display();
            }
        }
    };
}

#endif //SATURNITY_SATURNITY_HPP
