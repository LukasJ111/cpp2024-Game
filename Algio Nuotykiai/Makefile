all:
	g++ -I src/include -I src/include/SDL2 -L src/lib -o game main.cpp texture_manager.cpp game_loop.cpp player.cpp game_object.cpp Menu.cpp item.cpp Map.cpp Collision.cpp ECS/ECS.cpp Vector2D.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

clean:
	del game.exe game_loop.o main.o
