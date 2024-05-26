#include "game_object.h"
#include "texture_manager.h"

game_object::game_object(const char* texturesheet, int x, int y){

    objTexture = texture_manager::LoadTexture(texturesheet);

    xpos=x;
    ypos=y;

}

game_object::game_object(){

}

void game_object::Update(){
    xpos++;
    ypos++;

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
    SDL_RenderCopy(game_loop::renderer, objTexture, &srcRect, &destRect);
}

game_object::~game_object(){}
