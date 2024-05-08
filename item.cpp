#include "item.hpp"

item::item(){
    item_texture = NULL;
    name = "";
    description = "";
    damage = 0;
    range = 0;
}

item::~item(){
    SDL_DestroyTexture(item_texture);
}

void item::set_item_texture(const char* file, SDL_Renderer* ren){
    item_texture = texture_manager::LoadTexture(file, ren);
}

void item::set_name(std::string name){
    this->name = name;
}

void item::set_description(std::string description){
    this->description = description;
}

void item::set_weapon_stats(int damage, int range){
    this->damage = damage;
    this->range = range;
}

void item::show_item(SDL_Renderer* ren, int x, int y){
    SDL_Rect dest_rect;
    dest_rect.x = x;
    dest_rect.y = y;
    SDL_QueryTexture(item_texture, NULL, NULL, &dest_rect.w, &dest_rect.h);
    SDL_RenderCopy(ren, item_texture, NULL, &dest_rect);
}

int item::deal_damage(){
    return this->damage;
}

std::string item::get_description(){
    return this->description;
}

std::string item::get_name(){
    return this->name;
}

