##
## EPITECH PROJECT, 2023
## Saturnity
## File description:
## Makefile
##

INCLUDE = -I./include

BIN_NAME = server

SRC = main.cpp \
		src/*.cpp \
		src/packets/*.cpp

all:
	g++ -std=c++20 $(SRC) $(INCLUDE) -o $(BIN_NAME) -lpthread

client:
	g++ -std=c++20 client.cpp -o client -lpthread
