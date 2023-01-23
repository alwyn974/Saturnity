/*
** EPITECH PROJECT, 2023
** main.cpp
** File description:
** main.cpp
*/

#include <spdlog/spdlog.h>
#include <saturnity/Saturnity.hpp>

int main(int ac, char **av)
{
    spdlog::info("Welcome to Saturnity!");
    const sa::Test saturnity;
    saturnity.test();
    return 0;
}
