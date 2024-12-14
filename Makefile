build:
	gcc -Wall -std=c99 ./src/*.c -lSDL2 -lSDL2_ttf -lSDL2_mixer -o Air_Hockey_Game

run:
	./Air_Hockey_Game

clean:
	rm Air_Hockey_Game

