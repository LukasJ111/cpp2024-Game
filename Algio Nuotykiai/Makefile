all:
	g++ -I src/include -I src/include/SDL2 -L src/lib -o game main.cpp TextureManager.cpp GameLoop.cpp Player.cpp GameObject.cpp Menu.cpp item.cpp Map.cpp Collision.cpp ECS/ECS.cpp Vector2D.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

clean:
	del game.exe gameLoop.o main.o
