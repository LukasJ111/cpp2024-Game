#pragma once
#include "game_loop.h"

class game_object {

public:
    game_object();
    game_object(const char* texturesheet, SDL_Renderer* ren, int x, int y);
    ~game_object();

    void Update();
    void Render();

private:



protected:
    SDL_Texture* objTexture;
    int xpos;
    int ypos;

    SDL_Rect srcRect, destRect;
    SDL_Renderer* renderer;

};
