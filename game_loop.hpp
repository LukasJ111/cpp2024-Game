#ifndef game_loop_hpp
#define  game_loop_hpp

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL_image.h>

class game_loop{

public:
    game_loop();
    ~game_loop();

    void init(const char* title, int x_pos, int y_pos, int width, int height, bool fullscreen);
    void update();
    void render();
    void handle_events();
    void clean();
    bool running() {
        return is_running;
    };

private:
    int count = 0;
    bool is_running;
    SDL_Window *window;
    SDL_Renderer *renderer;
};

#endif