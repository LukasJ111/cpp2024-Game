#include "game_loop.hpp"

SDL_Texture* playerTex;
SDL_Rect srcR, destR;

game_loop::game_loop(){}
game_loop::~game_loop(){}

void game_loop::init(const char* title, int x_pos, int y_pos, int width, int height, bool fullscreen){

    int flags = 0;
    if(fullscreen){
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){

        window = SDL_CreateWindow(title, x_pos, y_pos, width, height, flags);

        renderer = SDL_CreateRenderer(window, -1, 0);

        if(renderer){
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Renderer is running.\n";
        }

        is_running = true;

    } 

    SDL_Surface* temp_surface = IMG_Load("assets/player.png");
    playerTex = SDL_CreateTextureFromSurface(renderer, temp_surface);
    SDL_FreeSurface(temp_surface);


}

void game_loop::handle_events(){
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type)
    {
    case SDL_QUIT: // Closes game
        is_running = false;
        break;
    
    default:
        break;
    }

}

void game_loop::update() {
    destR.h = 32;
    destR.w = 184;
}

void game_loop::render() {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, playerTex, NULL, &destR);
    SDL_RenderPresent(renderer);
}

void game_loop::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    IMG_Quit();
    std::cout << "Exiting game.\n";
}