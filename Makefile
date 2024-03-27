all:
	g++ -I src/include -L src/lib -o game main.cpp game_loop.cpp -lmingw32 -lSDL2main -lSDL2

clean:
	del game.exe game_loop.o main.o

