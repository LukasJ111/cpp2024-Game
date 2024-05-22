#pragma once 
#include <string>
#include "SDL.h"
#include "Components.h"
#include "../texture_manager.h"

class ColliderComponent : public Component 
{
public:

    SDL_Rect collider;
    std::string tag;

    SDL_Texture* tex;
    SDL_Rect srcR, destR;

    const char* path;

    TransformComponent* transform;

    ColliderComponent(std::string t)
    {
        tag = t;
    }

    ColliderComponent(std::string  t, int xpos, int ypos, int size)
    {
        tag = t;
        collider.x = xpos;
        collider.y = ypos;
        collider.h = collider.w = size;
    }

    //tcol.addComponent<ColliderComponent>("terrain", srcX, srcY,  xpos, ypos, tileSize, mapScale, file);

    ColliderComponent(std::string  t, int srcX, int srcY, int xpos, int ypos, int tileSize, int mapScale, const char* path)
    {

        this->path = path;

        tag = t;

        collider.x = xpos;
        collider.y = ypos;
        collider.h = collider.w = tileSize * mapScale;
        
        srcR.x=srcX;
        srcR.y=srcY;
        srcR.w=srcR.h=tileSize;

        destR.x=xpos;
        destR.y=ypos;
        destR.w=destR.h=tileSize*mapScale;

    }
   
    void init() override 
    {

        if(!entity->hasComponent<TransformComponent>())
        {
            entity->addComponent<TransformComponent>();
        }
        transform = &entity->getComponent<TransformComponent>();

        // TODO: pataisyt ihardcodeinima path'o. konfliktuoja init su konstruktoriais ir crashina jei naudoji kintamaji.
        tex = texture_manager::LoadTexture("assets/Map/map_ss.png");

    }

    void update() override
    {
        if(tag != "terrain" && tag != "collectible" && tag != "door") 
        {
            collider.x = static_cast<int>(transform->position.x);
            collider.y = static_cast<int>(transform->position.y);
            collider.w = transform->width * transform->scale;
            collider.h = transform->height * transform->scale;
        }
        destR.x = collider.x - game_loop::camera.x;
        destR.y = collider.y - game_loop::camera.y;
    }

    void draw() override
    {
        texture_manager::Draw(tex, srcR, destR, SDL_FLIP_NONE);
    }

    std::string getTag() {
        return tag;
    }

};