#include "game_loop.h"
#include "texture_manager.h"
#include "player.h"
#include "Map.h"
#include "Collision.h"

#include "ECS/Components.h"
#include "ECS/ECS.h"

#include "Vector2D.h"

Map* map;

Manager manager;

SDL_Renderer* game_loop::renderer=nullptr;
SDL_Event game_loop::event;

std::vector<ColliderComponent*> game_loop::colliders;

auto& player(manager.addEntity());
auto& wall(manager.addEntity());

const char* mapfile="assets/Map/TEMPp16x16.map";

enum groupLabels : std::size_t
{
    groupMap,
    groupPlayers,
    groupEnemies,
    groupColliders
};

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
    
    // LAIKINAI PAKEICIAU I 32 X 32 (is 16 x 16) ir pridejau kita laikina faila (prirasiau TEMP) KAD GERIAU MINIMALIAI ATRODYTU !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    Map::LoadMap("assets/Map/TEMPp16x16.map", 32, 32);

    player.addComponent<TransformComponent>(4);
    player.addComponent<SpriteComponent>("assets/Animacijos/PlayerPngs/PlayerRunRight/PlayerAnims.png", true);
    player.addComponent<KeyboardController>();
    player.addComponent<ColliderComponent>("player");
    player.addGroup(groupPlayers);


}


void game_loop::handle_events(){

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

    for (auto cc : colliders)
    {
        Collision::AABB(player.getComponent<ColliderComponent>(), *cc);
    }
}

auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnemies));


void game_loop::render() 
{
    SDL_RenderClear(renderer);

    for (auto& t : tiles)
    {
        t->draw();
    }

    for (auto& p : players)
    {
        p->draw();
    }

    for (auto& e : enemies)
    {
        e->draw();
    }
    SDL_RenderPresent(renderer);
}

void game_loop::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    IMG_Quit();
    std::cout << "Exiting game.\n";
}

void game_loop::AddTile(int srcX, int srcY, int xpos, int ypos)
{
    auto& tile(manager.addEntity());
    tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, mapfile);
    tile.addGroup(groupMap);
}
