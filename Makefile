all:
<<<<<<< HEAD
	g++ -I src/include -L src/lib -o game main.cpp texture_manager.cpp game_loop.cpp player.cpp game_object.cpp item.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
=======
	g++ -I src/include -I src/include/SDL2 -L src/lib -o game main.cpp texture_manager.cpp game_loop.cpp player.cpp game_object.cpp item.cpp Map.cpp Vector2D.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
>>>>>>> origin/KiprasK
clean:
	del game.exe game_loop.o main.o

