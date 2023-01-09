##
## EPITECH PROJECT, 2023
## Saturnity
## File description:
## Makefile
##

INCLUDE = -I./include

BIN_NAME = server

SRC = main.cpp \
	comm.pb.cc

all:
	g++ -std=c++20 $(SRC) $(INCLUDE) -o $(BIN_NAME) `pkg-config --cflags --libs protobuf`