/*
** EPITECH PROJECT, 2023
** Saturnity.hpp
** File description:
** Saturnity.hpp
*/

#ifndef SATURNITY_SATURNITY_HPP
#define SATURNITY_SATURNITY_HPP

#include "spdlog/spdlog.h"

namespace sa {
    class Test {
    public:
        Test() = default;

        inline void test() const {
            spdlog::info("Test");
        }
    };
}

#endif //SATURNITY_SATURNITY_HPP
