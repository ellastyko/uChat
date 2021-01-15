all: compile_all

COMPILER = gcc
CLIENT_FILES = client/src/*.c
SERVER_FILES = server/src/*.c

server: 
	gcc $(SERVER_FILES) -o out_server 

client: 
	gcc `pkg-config --cflags gtk+-3.0` -o out_client client.c `pkg-config --libs gtk+-3.0`
	#@gcc `pkg-config --cflags gtk+-3.0` -o client $(CLIENT_FILES) `pkg-config --libs gtk+-3.0`

compile_all: erver client

clear: 
	@rm -rf out_server
	@rm -rf out_client

# client: client.c 
# 	gcc `pkg-config --cflags gtk+-3.0` -o client client.c `pkg-config --libs gtk+-3.0