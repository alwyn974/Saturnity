/*
** EPITECH PROJECT, 2023
** Saturnity
** File description:
** main
*/

#include "comm.pb.h"

int main(void) {
    server::Player player = server::Player();

    player.set_username("Player One");
    std::cout << "Username: " <<player.username() << std::endl;
    player.clear_username();
    std::cout << "Username: " << player.username() << std::endl;
}