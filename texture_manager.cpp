#include "texture_manager.h"

SDL_Texture* texture_manager::LoadTexture(const char* file){
    SDL_Surface* temp_surface = IMG_Load(file);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(game_loop::renderer, temp_surface);
    SDL_FreeSurface(temp_surface);

    return tex;
}

void texture_manager::Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest) {
    SDL_RenderCopy(game_loop::renderer, tex, &src, &dest);
}
