#ifndef game_loop_h
#define game_loop_h

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "Vector2D.h"

class ColliderComponent;

class game_loop {

public:
    SDL_Texture* renderTarget = nullptr;
    game_loop();
    ~game_loop();

    void init(const char* title, int x_pos, int y_pos, int width, int height, bool fullscreen);
    void update();
    void render();
    void handle_events();
    void clean();
    bool running() { return is_running; };

    static SDL_Renderer *renderer;
    static SDL_Event event;
    static bool is_running;
    static SDL_Rect camera;

    struct Rat {
        Vector2D position;
        SDL_Texture* texture;
    };

    enum groupLabels : std::size_t {
        groupMap,
        groupPlayers,
        groupColliders,
        groupRats
    };

    bool gameOverSoundPlayed = false;
    Uint8* gameOverAudioBuffer = nullptr;
    Uint32 gameOverAudioLength;

    // audio
    float volume; 
    SDL_AudioDeviceID audioDevice;
    Uint8* audioBuffer;
    Uint32 audioLength;

    // rat
    Uint32 ratSpawnTimer = 0;
    const Uint32 ratSpawnInterval = 2500;
    void spawnRat();

private:
    SDL_Window *window;
    std::vector<Rat> rats;
};

#endif