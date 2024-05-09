all:
	g++ -I src/include -I src/include/SDL2 -L src/lib -o game main.cpp texture_manager.cpp game_loop.cpp player.cpp game_object.cpp item.cpp Map.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
clean:
	del game.exe game_loop.o main.o

