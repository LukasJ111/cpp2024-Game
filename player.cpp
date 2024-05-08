#include <player.hpp>

player::player(const char* file, SDL_Renderer* ren){
    player_texture = texture_manager::LoadTexture(file, ren);
    health = 5;                         // hit-points
    speed = 60;                         // Irrelevant speed number for now
}

player::~player(){
    SDL_DestroyTexture(player_texture);
}


// Stasts n stuff
void player::player_take_damage(int damage){
    health -= damage;
}

void player::player_heal(int heal){
    health += heal;
}

void player::player_add_item(item weapon){
    for(int i = 0; i < 2; i++){
        if(inventory[i].get_name() == ""){ // Blank space
            inventory[i] = weapon;
            break;
        }
    }
}

// Kipras and Kipras need to handle this logic (based off how they want to render the pngs)
void player::set_player_texture(const char* file, SDL_Renderer* ren){
    player_texture = texture_manager::LoadTexture(file, ren);
}

void player::animate_player_attack(const char* sheet, SDL_Renderer* ren, item weapon, int x, int y){
    weapon.show_item(ren, x, y); 
}

void player::animate_player_movement(const char* sheet, SDL_Renderer* ren, int x, int y){
    
}

void player::handle_input(SDL_Event key_pressed){
   
}

