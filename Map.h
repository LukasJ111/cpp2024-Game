#ifndef Map_H
#define Map_H

#include "game_loop.h"

class Map{

public:
    Map();
    ~Map();

    void LoadMap(int arr[20][25]);

    void DrawMap();

private:
    SDL_Rect src, dest;

    //Keisti pavadinimus as needed
    SDL_Texture* dirt;
    SDL_Texture* grass;
    SDL_Texture* water;

    //Keisti dydzius as needed
    int map[20][25];
};

#endif
