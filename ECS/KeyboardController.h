#ifndef KeyboardController_H
#define KeyboardController_H

#include "../game_loop.h"
#include "ECS.h"
#include "Components.h"

class KeyboardController : public Component
{
public:
    TransformComponent *transform;
    const Uint8* keystates = SDL_GetKeyboardState(NULL);

    void init() override
    {
        transform=&entity->getComponent<TransformComponent>();
    }

    void update() override
    {
        transform->velocity.x = 0;
        transform->velocity.y = 0;

        if (keystates[SDL_SCANCODE_W]) {
            transform->velocity.y = -1;
        }
        if (keystates[SDL_SCANCODE_A]) {
            transform->velocity.x = -1;
        }
        if (keystates[SDL_SCANCODE_S]) {
            transform->velocity.y = 1;
        }
        if (keystates[SDL_SCANCODE_D]) {
            transform->velocity.x = 1;
        }
        //SITAS BLOKAS IMPLEMENTUOJA TRUPUTI MAZIAU SMOOTH MOVEMENT, TODEL JIS UZKOMENTUOTAS.
        //PRIDEJAU ALTERNATYVIA IR GERESNE MOVEMENT SISTEMA, BET JEI PASIMESIM SU TUTORIALU DEL SIU PAKEITIMU GALIMA ATKOMENTUOT
        /*
        if(game_loop::event.type==SDL_KEYDOWN)
        {
            switch(game_loop::event.key.keysym.sym)
            {
                case SDLK_w:
                    transform->velocity.y=-1;
                    break;
                case SDLK_a:
                    transform->velocity.x=-1;
                    break;
                case SDLK_s:
                    transform->velocity.y=1;
                    break;
                case SDLK_d:
                    transform->velocity.x=1;
                    break;

                default:
                    break;
            }
        }
        if(game_loop::event.type==SDL_KEYUP)
        {
            switch(game_loop::event.key.keysym.sym)
            {
                case SDLK_w:
                    transform->velocity.y=0;
                    break;
                case SDLK_a:
                    transform->velocity.x=0;
                    break;
                case SDLK_s:
                    transform->velocity.y=0;
                    break;
                case SDLK_d:
                    transform->velocity.x=0;
                    break;

                default:
                    break;
            }
        }
         */


    }
};

#endif
