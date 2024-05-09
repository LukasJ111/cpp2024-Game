#pragma once
#include "game_loop.h"

class game_object {

public:
    game_object();
    game_object(const char* texturesheet, int x, int y);
    ~game_object();

    void Update();
    void Render();

private:



protected:

    int xpos;
    int ypos;

    SDL_Texture* objTexture;
    SDL_Rect srcRect, destRect;

};
