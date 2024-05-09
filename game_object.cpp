#include "game_object.h"
#include "texture_manager.h"

game_object::game_object(const char* texturesheet, SDL_Renderer* ren, int x, int y){

    renderer = ren;
    objTexture = texture_manager::LoadTexture(texturesheet, ren);

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
    SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
}

game_object::~game_object(){}
