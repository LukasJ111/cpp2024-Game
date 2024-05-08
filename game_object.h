#pragma once
#include "game_loop.h"

class game_object {

public:
    game_object();
    game_object(const char* texturesheet, SDL_Renderer* ren);
    ~game_object();

    void Update();
    void Render();

private:

    int xpos;
    int ypos;

    SDL_Texture* objTexture;
    SDL_Rect srcRect, destRect;
    SDL_Renderer* renderer;

};
