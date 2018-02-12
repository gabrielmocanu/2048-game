build: game_2048.o
	gcc game_2048.c -lncurses -Wall -o game_2048

encoder.o: game_2048.c
	gcc -c game_2048.c

run: game_2048
	./game_2048

clean:
	rm *.o game_2048
