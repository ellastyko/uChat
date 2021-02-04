COMPILER = gcc
CLIENT_FILES = client.c
GTK = `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0`


all: 
	$(clear)
	$(COMPILER) -Wl,--export-dynamic -o client $(CLIENT_FILES)  $(GTK)
	#$(COMPILER) -o client $(CLIENT_FILES) $(GTK)
	./client
	
clear: 
	rm -rf client