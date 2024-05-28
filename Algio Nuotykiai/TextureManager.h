#pragma once

#include "GameLoop.h"

class texture_manager {

    public:
        static SDL_Texture* LoadTexture(const char* file);
        static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip);
        static void Draw(SDL_Texture* tex, SDL_Rect dest, SDL_RendererFlip flip);

};