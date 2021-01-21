all: clear server client

COMPILER = gcc
CLIENT_FILES = Client/src/*.c
SERVER_FILES = Server/src/*.c
LIBS = lib/*.c 

GTK = `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0`
FLAGS = -std=c11 

server: 
	cd Server/src/
	$(COMPILER) $(FLAGS) $(LIBS) -o server $(SERVER_FILES) -pthread -lsqlite3

client: 
	cd Client/src/
	$(COMPILER) -o client $(LIBS) $(CLIENT_FILES) $(GTK)

clear: 
	rm -rf server
	rm -rf client
	rm -rf obj











	