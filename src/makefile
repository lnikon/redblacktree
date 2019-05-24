SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
CC = g++
LDFALGS = -g -fsanitize=address -Wall -std=c++17

main: $(SRC)
	$(CC) -o $@ $^  $(LDFALGS)

.PHONY: clean

clean:
	rm -f main
