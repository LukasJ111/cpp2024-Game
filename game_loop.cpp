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

SDL_Rect game_loop::camera={0,0,800,640};

std::vector<ColliderComponent*> game_loop::colliders;

bool game_loop::is_running=false;

auto& player(manager.addEntity());
auto& wall(manager.addEntity());

const char* mapfile="assets/Map/grass.png"; //PAKEISTI SU PILNO MAPO PNG

enum groupLabels : std::size_t
{
    groupMap,
    groupPlayers,
    groupEnemies,
    groupColliders
};

auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnemies));

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

    camera.x=player.getComponent<TransformComponent>().position.x-400;
    camera.y=player.getComponent<TransformComponent>().position.y-320;

    if(camera.x<0) camera.x=0;
    if(camera.y<0) camera.y=0;
    if(camera.x>camera.w) camera.x=camera.w;
    if(camera.y>camera.h) camera.y=camera.h;

    /*
    Vector2D pVel=player.getComponent<TransformComponent>().velocity;
    int pSpeed=player.getComponent<TransformComponent>().speed;


    for(auto t: tiles)
    {
        t->getComponent<TileComponent>().destRect.x+=-(pVel.x*pSpeed);
        t->getComponent<TileComponent>().destRect.y+=-(pVel.y*pSpeed);
    }
     */
}




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
