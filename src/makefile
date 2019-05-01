SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
CC = g++
LDFALGS = -Wall -std=c++17

main: $(SRC)
	$(CC) -o $@ $^  $(LDFALGS)
