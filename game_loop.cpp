#include "game_loop.h"
#include "texture_manager.h"
#include "player.h"
#include "Map.h"

#include "ECS/Components.h"
#include "ECS/ECS.h"

Map* map;

Manager manager;

SDL_Renderer* game_loop::renderer=nullptr;
auto& player(manager.addEntity());

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

    //player = new Player("assets/Animacijos/PlayerPngs/PlayerRunRight/PlayerRunRight (1).png", 0 ,0); // simple loading
    map=new Map();

    player.addComponent<PositionComponent>(300, 200);
    player.addComponent<SpriteComponent>("assets/Animacijos/PlayerPngs/PlayerRunRight/PlayerRunRight (1).png");

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

    manager.refresh();
    manager.update();

}

void game_loop::render() {
    SDL_RenderClear(renderer);
    map->DrawMap(); // map draw'inam pirma, kad zaidejas/kiti objektai butu vaizduojamas ANT jo, o ne PO juo.
    manager.draw();
    SDL_RenderPresent(renderer);
}

void game_loop::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    IMG_Quit();
    std::cout << "Exiting game.\n";
}