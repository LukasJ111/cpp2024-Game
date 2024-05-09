
#ifndef SpriteComponent_H
#define SpriteComponent_H

#include "Components.h"
#include "SDL.h"

class SpriteComponent : public Component
{
private:
    TransformComponent *transform;
    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;


public:
    SpriteComponent()=default;
    SpriteComponent(const char* path)
    {
        setTex(path);
    }

    void setTex(const char* path)
    {
        texture=texture_manager::LoadTexture(path);
    }

    void init() override
    {
        transform=&entity->getComponent<TransformComponent>();

        srcRect.x=srcRect.y=0;
        srcRect.w=srcRect.h=32;
        destRect.w=destRect.h=32;
    }

    void update() override
    {
        destRect.x=(int)transform->position.x;
        destRect.y=(int)transform->position.y;
    }

    void draw() override
    {
        texture_manager::Draw(texture, srcRect, destRect);
    }
};
#endif
