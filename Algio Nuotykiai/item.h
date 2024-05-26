#ifndef item_h
#define  item_h

#include "texture_manager.h"
#include <string>

    class item{

    private:

        SDL_Texture* item_texture;
        std::string name;
        std::string description;

        // Weapon type items
        int damage;
        int range;

    public:
        item();
        ~item();

        void set_item_texture(const char* file);
        void set_name(std::string name);
        void set_description(std::string description);
        void set_weapon_stats(int damage, int range);

        std::string get_name();
        std::string get_description();
        

        void show_item(SDL_Renderer* ren, int x, int y); // x, y - will later be used to update position relative to playewr
        int deal_damage();                               // Will deal damage to enemy type objects later    
    };

#endif