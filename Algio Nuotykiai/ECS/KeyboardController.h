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

    SpriteComponent *sprite;

    void init() override
    {
        transform=&entity->getComponent<TransformComponent>();
        sprite = &entity->getComponent<SpriteComponent>();
    }


    // Sitas visas metodas labai netobulas gali reiket tobulint. paspaudus h veikejas trenkia, bet jei ir vaikstai ir trankai ten kazkokios nesamones biski prasideda
    void update() override
    {   
        transform->velocity.x = 0;
        transform->velocity.y = 0;

        char direction = sprite->getDirection();

        switch (direction)
        {
        case 'W':
            sprite->Play("IdleUp");            
            break;
        case 'A':
            sprite->Play("Idle");
            sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
            break;
        case 'S':
            sprite->Play("IdleUp");
            sprite->spriteFlip = SDL_FLIP_VERTICAL;
            break;
        case 'D':
            sprite->Play("Idle");
            break;
        default:
            break;
        }
        //sprite->spriteFlip = SDL_FLIP_NONE;

        if (keystates[SDL_SCANCODE_W]) {
            transform->velocity.y = -1;
            sprite->Play("WalkUp");
            sprite->setDirection('W');
            sprite->spriteFlip = SDL_FLIP_NONE;
        }
        if (keystates[SDL_SCANCODE_A]) {
            transform->velocity.x = -1;
            sprite->Play("Walk");
            sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
            sprite->setDirection('A');
        }
        if (keystates[SDL_SCANCODE_S]) {
            transform->velocity.y = 1;
            sprite->Play("WalkUp");
            sprite->spriteFlip = SDL_FLIP_VERTICAL;
            sprite->setDirection('S');
        }
        if (keystates[SDL_SCANCODE_D]) {
            transform->velocity.x = 1;
            sprite->Play("Walk");
            sprite->spriteFlip = SDL_FLIP_NONE;
            sprite->setDirection('D');
        }

        if (keystates[SDL_SCANCODE_H] && (direction == 'A' || direction == 'D')) {
            sprite->Play("HitBH");
        }

        if (keystates[SDL_SCANCODE_H] && (direction == 'W' || direction == 'S')) {
            sprite->Play("HitUpBH");
        }

        if (keystates[SDL_SCANCODE_ESCAPE]) {
            game_loop::is_running=false;
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
