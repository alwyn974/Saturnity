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
	cmake -B build -S .
	cmake --build ./build -j$(nproc)

clean:
	rm client
	rm server

fclean: clean


.PHONY: client