/*
** EPITECH PROJECT, 2023
** main.cpp
** File description:
** main.cpp
*/

#include <spdlog/spdlog.h>

#include "saturnity/Saturnity.hpp"

int main(int ac, char **av)
{
    spdlog::info("Welcome to Saturnity!");
    std::vector<byte_t> test = {
        0x1, 0x2
    };
    std::vector<byte_t> copy = test;
    copy[0] = 0x2;

    spdlog::info("{} {} - {}", test[0], copy[0], sizeof(bool));

    return 0;
}
