COMPILER = gcc
CLIENT_FILES = *.c
GTK = `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0`


client: 
	$(COMPILER) -o client $(CLIENT_FILES) $(GTK)
clear: 
	rm -rf client