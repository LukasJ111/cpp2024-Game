#include "Player.h"
#include "item.h"

Player::Player(const char* texturesheet, int x, int y)
        : game_object(texturesheet, x, y){
    health = 5;                         // hit-points
    speed = 60;                         // Irrelevant speed number for now
}

Player::~Player()= default;


// Stasts n stuff
void Player::player_take_damage(int damage){
    health -= damage;
}

void Player::player_heal(int heal){
    health += heal;
}

void Player::player_add_item(item weapon){
    for(int i = 0; i < 2; i++){
        if(inventory[i].get_name() == ""){ // Blank space
            inventory[i] = weapon;
            break;
        }
    }
}

// Kipras and Kipras need to handle this logic (based off how they want to render the pngs)
void Player::set_player_texture(const char* file, SDL_Renderer* ren){
    objTexture = texture_manager::LoadTexture(file);
}

void Player::animate_player_attack(const char* sheet, SDL_Renderer* ren, item weapon, int x, int y){
    weapon.show_item(ren, x, y); 
}

void Player::animate_player_movement(const char* sheet, SDL_Renderer* ren, int x, int y){
    
}

void Player::handle_input(SDL_Event key_pressed){
   
}

