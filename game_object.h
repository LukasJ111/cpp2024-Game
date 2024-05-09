#pragma once
#include "game_loop.h"

class game_object {

public:
    game_object();
<<<<<<< HEAD
    game_object(const char* texturesheet, SDL_Renderer* ren);
=======
    game_object(const char* texturesheet, int x, int y);
>>>>>>> origin/KiprasK
    ~game_object();

    void Update();
    void Render();

private:

<<<<<<< HEAD
=======


protected:

>>>>>>> origin/KiprasK
    int xpos;
    int ypos;

    SDL_Texture* objTexture;
    SDL_Rect srcRect, destRect;
<<<<<<< HEAD
    SDL_Renderer* renderer;
=======
>>>>>>> origin/KiprasK

};
