//
// Created by Audrius on 2024-05-24.
//

#ifndef CPP2024_GAME_PONULIO_MENU_H
#define CPP2024_GAME_PONULIO_MENU_H
#include "SDL2/SDL_rect.h"
#include "texture_manager.h"

class Menu {
public:
     void show_menu(SDL_Rect dest);
private:
    void drawButton(SDL_Rect button, bool isMouseOver, SDL_Texture* bwTexture, SDL_Texture* colorTexture, SDL_Rect dest);
    bool isMouseOverButton(SDL_Rect button, int mouseX, int mouseY);
};


#endif //CPP2024_GAME_PONULIO_MENU_H
