#pragma once

#include "ECS.h"
#include "SDL.h"

class TileComponent : public Component
{
public:

    SDL_Texture* texture;
    SDL_Rect srcRect, destRect;

    Vector2D position;

    TileComponent() = default;

    ~TileComponent()
    {
        SDL_DestroyTexture(texture);
    }


    TileComponent(int srcX, int srcY, int xpos, int ypos, const char* path)
    {
        texture=texture_manager::LoadTexture(path);

        position.x=xpos;
        position.y=ypos;

        srcRect.x=srcX;
        srcRect.y=srcY;
        srcRect.w=srcRect.h=32;

        destRect.x=xpos;
        destRect.y=ypos;
        destRect.w=destRect.h=64;

    }

    void update() override
    {
        destRect.x=position.x-game_loop::camera.x;
        destRect.y=position.y-game_loop::camera.y;
    }

    void draw() override
    {
        texture_manager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
    }

};