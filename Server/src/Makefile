COMPILER = gcc
SERVER_FILES = *.c
FLAGS = -pthread #-std=c11 -Wall -Wextra -Werror -Wpedantic

server: 
	$(COMPILER) $(FLAGS) $(SERVER_FILES) -o server

clear: 
	rm -rf server