#ifndef game_loop_h
#define  game_loop_h

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

class ColliderComponent;

class game_loop{

public:
    game_loop();
    ~game_loop();

    void init(const char* title, int x_pos, int y_pos, int width, int height, bool fullscreen);
    void update();
    void render();
    void handle_events();
    void clean();
    bool running() { return is_running; };

    static void AddTile(int srcX, int srcY, int xpos, int ypos);
    static SDL_Renderer *renderer;
    static SDL_Event event;
    static std::vector<ColliderComponent*> colliders;
    static bool is_running;
private:
    SDL_Window *window;
};

#endif