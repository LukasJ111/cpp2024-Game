#include "game_loop.h"
#include "texture_manager.h"
#include "player.h"
#include "Map.h"
#include "Collision.h"

#include "ECS/Components.h"
#include "ECS/ECS.h"

#include "Vector2D.h"

#include "SDL_image.h"

Map* map;

Manager manager;

SDL_Renderer* game_loop::renderer=nullptr;
SDL_Event game_loop::event;

SDL_Rect game_loop::camera={0,0,800,640};

bool game_loop::is_running=false;

auto& player(manager.addEntity());

static bool gameOver = false;

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
    map=new Map("assets/Map/map_ss.png", 4, 16);
    
    map->LoadMap("assets/Map/map.map", 32, 32);

    player.addComponent<TransformComponent>(4);
    player.addComponent<SpriteComponent>("assets/Animacijos/PlayerPngs/PlayerRunRight/PlayerAnims.png", true);
    player.addComponent<KeyboardController>();
    player.addComponent<ColliderComponent>("player");
    player.addGroup(groupPlayers);


}

auto& tiles(manager.getGroup(game_loop::groupMap));
auto& players(manager.getGroup(game_loop::groupPlayers));
auto& colliders(manager.getGroup(game_loop::groupColliders));

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

void game_loop::update() 
{

    SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;
    Vector2D playerPos = player.getComponent<TransformComponent>().position;

    manager.refresh();
    manager.update();

    for (auto& c : colliders)
    {
        std::string tag=c->getComponent<ColliderComponent>().getTag();
        SDL_Rect  cCol = c->getComponent<ColliderComponent>().collider;
        if(Collision::AABB(cCol, playerCol))
        {
            player.getComponent<TransformComponent>().position = playerPos;
            if(tag == "collectible") {

                // IHARDCODEINOM
                if(playerPos.x > 1400) {
                    for (auto& d : colliders) {
                        if(d->getComponent<ColliderComponent>().getTag() == "door") {

                            d->destroy();
                        }
                    }
                }

                if(playerPos.y < 300 && playerPos.x > 850 && playerPos.x < 1050) {
                    
                    gameOver = true;
                    //texture_manager::LoadTexture("assets/Map/map_ss.png");
                }

                c->destroy();
            }
        }
    }

    camera.x=player.getComponent<TransformComponent>().position.x-400;
    camera.y=player.getComponent<TransformComponent>().position.y-320;

    if(camera.x<0) camera.x=0;
    if(camera.y<0) camera.y=0;

    // 32 ihardcodeinom
    if(camera.x>(32*map->getScaledSize())-camera.w) camera.x=(32*map->getScaledSize())-camera.w;
    if(camera.y>(32*map->getScaledSize())-camera.h) camera.y=(32*map->getScaledSize())-camera.h;

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

    for (auto& c : colliders)
    {
        c->draw();
    }

    for (auto& p : players)
    {
        p->draw();
    }

    if(gameOver) {

        auto texture = texture_manager::LoadTexture("assets/Map/pabaiga.png");

        SDL_Rect dest = camera;

        dest.x -= 560;

        texture_manager::Draw(texture, dest, SDL_FLIP_NONE);

        for (auto& t : tiles)
        {
            t->destroy();
        }

        for (auto& c : colliders)
        {
            c->destroy();
        }

        for (auto& p : players)
        {
            p->destroy();
        }

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
