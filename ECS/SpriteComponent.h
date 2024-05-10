
#ifndef SpriteComponent_H
#define SpriteComponent_H

#include "Components.h"
#include "SDL.h"
#include "../texture_manager.h"
#include "Animation.h"
#include <map>

class SpriteComponent : public Component
{
private:
    TransformComponent *transform;
    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;

    bool animated = false;
    int frames = 0;
    int speed = 100;

public:

    int animIndex = 0;

    std::map<const char*, Animation> animations;

    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

    SpriteComponent()=default;
    SpriteComponent(const char* path)
    {
        setTex(path);
    }

    SpriteComponent(const char* path, bool isAnimated)
    {
        animated = isAnimated;

        // Reiks pakeisti pagal savo animacijas
        Animation idle = Animation(0, 1, 100);
        Animation walk = Animation(1, 4, 100);
        Animation walkUp = Animation(2, 4, 100);

        animations.emplace("Idle", idle);
        animations.emplace("Walk", walk);
        animations.emplace("WalkUp", walkUp);

        Play("Idle");

        setTex(path);
    }

    ~SpriteComponent()
    {
        SDL_DestroyTexture(texture);
    }

    void setTex(const char* path)
    {
        texture=texture_manager::LoadTexture(path);
    }

    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();

        srcRect.x = srcRect.y = 0;
        srcRect.w = transform->width;
        srcRect.h = transform->height;

    }

    void update() override
    {

        if (animated)
        {
            srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
        }

        srcRect.y = animIndex * transform->height;

        destRect.x = static_cast<int>(transform->position.x)-game_loop::camera.x;
        destRect.y = static_cast<int>(transform->position.y)-game_loop::camera.y;
        destRect.w = transform->width * transform->scale;
        destRect.h = transform->height * transform->scale;
    }

    void draw() override
    {
        texture_manager::Draw(texture, srcRect, destRect, spriteFlip);
    }

    void Play(const char* animName)
    {
        frames = animations[animName].frames;
        animIndex = animations[animName].index;
        speed = animations[animName].speed;
    }
};
#endif
