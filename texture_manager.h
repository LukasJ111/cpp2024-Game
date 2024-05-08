#pragma once

#include "game_loop.h"

class texture_manager {

    public:
        static SDL_Texture* LoadTexture(const char* file, SDL_Renderer* ren);

};