#ifndef player_h
#define  player_h

//#include "texture_manager.h"
#include <string>
#include "item.h"
#include <SDL2/SDL_events.h>
#include "game_object.h"

class Player : public game_object {

public:

    // Player look
    SDL_Texture* player_texture;
    int health;
    item inventory[2]; // Max 2 weapons (hard-coded) 
    int speed;

public:
    Player(const char* texturesheet, SDL_Renderer* ren);
    ~Player();


    // Animations
    void set_player_texture(const char* file, SDL_Renderer* ren);
    void animate_player_movement(const char* sheet, SDL_Renderer* ren, int x, int y);
    void animate_player_attack(const char* sheet, SDL_Renderer* ren, item weapon, int x, int y); // Position need relevant to where it was swung
    
    void handle_input(SDL_Event key_pressed); // unsure how to do this  yet

    // void
    void player_take_damage(int damage);    // Slow player after taking damage :D
    void player_heal(int heal);             // Regeneration effect later in game loop logic (once every N seconds n stuff)
    void player_add_item(item weapon);

    SDL_Texture* objTexture;
    SDL_Rect srcRect, destRect;
    SDL_Renderer* renderer;

};


#endif