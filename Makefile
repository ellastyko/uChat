all: clear sr cl

COMPILER = gcc
CLIENT_FILES = Client/src/*.c
SERVER_FILES = Server/src/*.c
LIBS = lib/*.c 

GTK = `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0` -export-dynamic
FLAGS = -std=c11 -Wall -Wextra -Wpedantic #-Werror

sr: 
	cd Server/src/
	$(COMPILER) $(FLAGS) $(LIBS) $(SERVER_FILES) -pthread -lsqlite3 
	#delete pthread in mac
	@mv a.out server.o

cl: 
	rm -rf client.o
	cd Client/src/
	$(COMPILER) $(FLAGS) $(LIBS) $(CLIENT_FILES) $(GTK)
	@mv a.out client.o

clear: 
	rm -rf server.o
	rm -rf client.o












	