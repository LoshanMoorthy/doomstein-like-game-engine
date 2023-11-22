all:
	g++ -Iinclude -Iinclude/SDL2 -Llib -o main src/*.c -lmingw32 -lSDL2main -lSDL2
