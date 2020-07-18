CC = gcc
CC_FLAGS = -Wall -Wextra -pedantic

build: dhcp.o main.o
	$(CC) ./bin/dhcp.o ./bin/main.o -o ./bin/dhcp $(CC_FLAGS)

main.o: ./src/main.c
	$(CC) -c ./src/main.c -o ./bin/main.o $(CC_FLAGS)

dhcp.o: ./src/dhcp.c ./src/dhcp.h
	$(CC) -c ./src/dhcp.c -o ./bin/dhcp.o $(CC_FLAGS)

clean:
	rm -r ./bin/*

