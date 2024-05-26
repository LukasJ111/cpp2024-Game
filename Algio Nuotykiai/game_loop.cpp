#include "game_loop.h"
#include "texture_manager.h"
#include "player.h"
#include "Map.h"
#include "Collision.h"
#include "SDL_audio.h" // uhh
#include "ECS/Components.h"
#include "ECS/ECS.h"
#include "Vector2D.h"
#include "Menu.h"
#include "SDL_image.h"
#include <cmath> 

Map* map;

Manager manager;

SDL_Renderer* game_loop::renderer = nullptr;
SDL_Event game_loop::event;

SDL_Rect game_loop::camera = {0, 0, 800, 640};

bool game_loop::is_running = false;
static bool is_Started = false;

auto& player(manager.addEntity());

static bool gameOver = false;

game_loop::game_loop() : volume(0.01f) {} 
game_loop::~game_loop() {}

void audioCallback(void* userdata, Uint8* stream, int len) {
    game_loop* game = (game_loop*)userdata;

    if (game->audioLength == 0 && game->gameOverAudioLength == 0) {
        return;
    }

    SDL_memset(stream, 0, len);

    if (game->gameOverSoundPlayed) {
        len = (len > game->gameOverAudioLength ? game->gameOverAudioLength : len);
        for (int i = 0; i < len; ++i) {
            stream[i] = (Uint8)(game->gameOverAudioBuffer[i] * game->volume);
        }
        game->gameOverAudioBuffer += len;
        game->gameOverAudioLength -= len;
    } else {
        len = (len > game->audioLength ? game->audioLength : len);
        for (int i = 0; i < len; ++i) {
            stream[i] = (Uint8)(game->audioBuffer[i] * game->volume);
        }
        game->audioBuffer += len;
        game->audioLength -= len;

        if (game->audioLength <= 0) {
            SDL_AudioSpec wavSpec;
            SDL_LoadWAV("assets/Music/background.wav", &wavSpec, &game->audioBuffer, &game->audioLength);
        }
    }
}

void renderNightOverlay(SDL_Renderer* renderer) {
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 1, 1, 9, 200); // rgba
    SDL_Rect overlay = {0, 0, 800, 640};
    SDL_RenderFillRect(renderer, &overlay);
}

void game_loop::init(const char* title, int x_pos, int y_pos, int width, int height, bool fullscreen) {
    int flags = SDL_WINDOW_SHOWN;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        window = SDL_CreateWindow(title, x_pos, y_pos, width, height, flags);
        renderer = SDL_CreateRenderer(window, -1, 0);

        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Renderer is running.\n";
        }

        // sound
        SDL_Init(SDL_INIT_AUDIO);
        SDL_AudioSpec wavSpec;
        SDL_LoadWAV("assets/Music/background.wav", &wavSpec, &audioBuffer, &audioLength);
        wavSpec.callback = audioCallback;
        wavSpec.userdata = this;
        audioDevice = SDL_OpenAudioDevice(nullptr, 0, &wavSpec, nullptr, 0);
        SDL_PauseAudioDevice(audioDevice, 0);

        is_running = true;
        renderTarget = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 800, 640);
    }

    map = new Map("assets/Map/map_ss.png", 4, 16);
    map->LoadMap("assets/Map/map.map", 32, 32);

    player.addComponent<TransformComponent>(4);
    player.addComponent<SpriteComponent>("assets/Animacijos/PlayerPngs/PlayerRunRight/PlayerAnims.png", true);
    player.addComponent<KeyboardController>();
    player.addComponent<ColliderComponent>("player");
    player.addGroup(groupPlayers);

    ratSpawnTimer = SDL_GetTicks();
}

auto& tiles(manager.getGroup(game_loop::groupMap));
auto& players(manager.getGroup(game_loop::groupPlayers));
auto& colliders(manager.getGroup(game_loop::groupColliders));

void game_loop::handle_events() {
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            is_running = false;
            break;
        default:
            break;
    }
}

void game_loop::update() {
    TransformComponent& transform = player.getComponent<TransformComponent>();
    ColliderComponent& collider = player.getComponent<ColliderComponent>();
    Vector2D playerOldPos = transform.position;
    transform.position += Vector2D(transform.velocity.x * transform.speed, 0);
    bool can_move_x = true;

    manager.refresh();
    manager.update();

    Vector2D playerPos = transform.position;
    SDL_Rect playerCol = collider.collider;
    for (auto& c : colliders) {
        std::string tag = c->getComponent<ColliderComponent>().getTag();
        SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;

        if (Collision::AABB(cCol, playerCol)) {
            can_move_x = false;

            if (tag == "collectible") {
                if (playerPos.x > 1400) {
                    for (auto& d : colliders) {
                        if (d->getComponent<ColliderComponent>().getTag() == "door") {
                            d->destroy();
                        }
                    }
                }

                if (playerPos.y < 300 && playerPos.x > 850 && playerPos.x < 1050) {
                    gameOver = true;
                }

                c->destroy();
            }
        }
    }

    if (!can_move_x) {
        transform.position = playerOldPos;
    } else {
        playerOldPos = transform.position;
    }

    transform.position += Vector2D(0, transform.velocity.y * transform.speed);
    bool can_move_y = true;
    collider.update();

    playerPos = transform.position;
    playerCol = collider.collider;
    for (auto& c : colliders) {
        std::string tag = c->getComponent<ColliderComponent>().getTag();
        SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;

        if (Collision::AABB(cCol, playerCol)) {
            can_move_y = false;

            if (tag == "collectible") {
                if (playerPos.x > 1400) {
                    for (auto& d : colliders) {
                        if (d->getComponent<ColliderComponent>().getTag() == "door") {
                            d->destroy();
                        }
                    }
                }

                if (playerPos.y < 300 && playerPos.x > 850 && playerPos.x < 1050) {
                    gameOver = true;
                }

                c->destroy();
            }
        }
    }

    if (!can_move_y) {
        transform.position = playerOldPos;
    }

    camera.x = player.getComponent<TransformComponent>().position.x - 400;
    camera.y = player.getComponent<TransformComponent>().position.y - 320;

    if (camera.x < 0) camera.x = 0;
    if (camera.y < 0) camera.y = 0;

    if (camera.x > (32 * map->getScaledSize()) - camera.w) camera.x = (32 * map->getScaledSize()) - camera.w;
    if (camera.y > (32 * map->getScaledSize()) - camera.h) camera.y = (32 * map->getScaledSize()) - camera.h;

    if (gameOver) {
        rats.clear();
        return;
    }

    Uint32 currentTime = SDL_GetTicks();
    if (currentTime > ratSpawnTimer + ratSpawnInterval) {
        spawnRat();
        ratSpawnTimer = currentTime;
    }

    for (auto it = rats.begin(); it != rats.end(); ) {
        Rat& rat = *it;

        Vector2D velocity(0, 0);
        if (rat.position.x < playerPos.x) {
            velocity.x = 1;
        } else if (rat.position.x > playerPos.x) {
            velocity.x = -1;
        }

        if (rat.position.y < playerPos.y) {
            velocity.y = 1;
        } else if (rat.position.y > playerPos.y) {
            velocity.y = -1;
        }

        rat.position += velocity;

        if (fabs(rat.position.x - playerPos.x) < 10 && fabs(rat.position.y - playerPos.y) < 10) {
            it = rats.erase(it); 
        } else {
            ++it;
        }
    }
}

void game_loop::render() {
    SDL_SetRenderTarget(renderer, renderTarget);
    SDL_RenderClear(renderer);

    for (auto& t : tiles) {
        t->draw();
    }

    for (auto& c : colliders) {
        c->draw();
    }

    for (auto& p : players) {
        p->draw();
    }

    if (!gameOver) {
        for (auto& rat : rats) {
            SDL_Rect dest;
            dest.x = static_cast<int>(rat.position.x - camera.x);
            dest.y = static_cast<int>(rat.position.y - camera.y);
            dest.w = 32; 
            dest.h = 64; 
            SDL_RenderCopy(renderer, rat.texture, nullptr, &dest);
        }
    }

    if (gameOver) {
        if (!gameOverSoundPlayed) {
            SDL_CloseAudioDevice(audioDevice);

            SDL_AudioSpec gameOverWavSpec;
            if (SDL_LoadWAV("assets/music/gameover.wav", &gameOverWavSpec, &gameOverAudioBuffer, &gameOverAudioLength) == nullptr) {
                std::cerr << "Failed to load game over WAV file! SDL_Error: " << SDL_GetError() << std::endl;
            }
            gameOverWavSpec.callback = audioCallback;
            gameOverWavSpec.userdata = this;
            audioDevice = SDL_OpenAudioDevice(nullptr, 0, &gameOverWavSpec, nullptr, 0);
            SDL_PauseAudioDevice(audioDevice, 0);
            gameOverSoundPlayed = true;
        }

        auto texture = texture_manager::LoadTexture("assets/Map/pabaiga.png");
        SDL_Rect dest = camera;
        dest.x -= 560;
        texture_manager::Draw(texture, dest, SDL_FLIP_NONE);

        for (auto& t : tiles) {
            t->destroy();
        }

        for (auto& c : colliders) {
            c->destroy();
        }

        for (auto& p : players) {
            p->destroy();
        }
    }

    if (!is_Started) {
        Menu menu;
        // menu.show_menu(camera);
    }
    renderNightOverlay(renderer);

    SDL_SetRenderTarget(renderer, nullptr);
    int windowWidth, windowHeight;
    SDL_GetRendererOutputSize(renderer, &windowWidth, &windowHeight);
    SDL_Rect dstRect = {0, 0, windowWidth, windowHeight};
    SDL_RenderCopy(renderer, renderTarget, nullptr, &dstRect);

    SDL_RenderPresent(renderer);
}

void game_loop::clean() {
    SDL_DestroyTexture(renderTarget);
    SDL_CloseAudioDevice(audioDevice);
    SDL_FreeWAV(audioBuffer);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    IMG_Quit();
    std::cout << "Exiting game.\n";
}

void game_loop::spawnRat() {
    Rat rat;
    rat.texture = texture_manager::LoadTexture("assets/Animacijos/EnemyPngs/Scary.png");

    Vector2D playerPos = player.getComponent<TransformComponent>().position;

    for (int i = 0; i < 5; i++) {
        rat.position.x = playerPos.x + (rand() % (3 * 32)) - (3 * 16);
        rat.position.y = playerPos.y + (rand() % (3 * 32)) - (3 * 16);
        rats.push_back(rat);    
    }
}
