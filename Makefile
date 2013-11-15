all:
	gcc player/player.c -o player/player
	g++ server/server.c -o server/server

clean:
	rm -f player/player
	rm -f server/server
