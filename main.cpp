#include "game_loop.h"

game_loop *game = nullptr;

int main( int argc, char *argv[] )
{

    const int FPS = 60;
    const int frameDelay = 1000 / FPS; // Max time between frames
    Uint32 frameStart;
    int frameTime;

    game = new game_loop();

    game->init("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

    while(game->running()){

        frameStart = SDL_GetTicks();

        game->handle_events();
        game->update();
        game->render();

        frameTime = SDL_GetTicks() - frameStart;

        if(frameDelay > frameTime){ // Limiting frame rate (speed at which character moves)
            SDL_Delay(frameDelay - frameTime);
        }
    }

    game->clean();

    return 0;

}