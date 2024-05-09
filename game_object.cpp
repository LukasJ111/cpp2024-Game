#include "game_object.h"
#include "texture_manager.h"

<<<<<<< HEAD
game_object::game_object(const char* texturesheet, SDL_Renderer* ren){

    renderer = ren;
    objTexture = texture_manager::LoadTexture(texturesheet, ren);
=======
game_object::game_object(const char* texturesheet, int x, int y){

    objTexture = texture_manager::LoadTexture(texturesheet);

    xpos=x;
    ypos=y;
>>>>>>> origin/KiprasK

}

game_object::game_object(){

}

void game_object::Update(){
    xpos++;
    ypos++;

<<<<<<< HEAD
    xpos=0;
    ypos=0;

=======
>>>>>>> origin/KiprasK
    srcRect.h = 32;
    srcRect.w = 32;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x=xpos;
    destRect.y=ypos;
    destRect.w=srcRect.w * 2;
    destRect.h=srcRect.h * 2;
}
void game_object::Render(){
<<<<<<< HEAD
    SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
=======
    SDL_RenderCopy(game_loop::renderer, objTexture, &srcRect, &destRect);
>>>>>>> origin/KiprasK
}

game_object::~game_object(){}
