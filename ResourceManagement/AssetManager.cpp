//
// Created by Acer on 2024-03-17.
//

#include "AssetManager.h"

namespace ResourceMng {
    AssetManager::AssetManager(SDL_Renderer *renderer) : renderer(renderer) {};

    std::shared_ptr<TextureResource> AssetManager::loadTexture(const std::string& path) {
        {
            auto it = resources.find(path);
            if (it != resources.end()) {
                // Resource already loaded, return it
                return std::static_pointer_cast<TextureResource>(it->second);
            }

            SDL_Surface* surface = IMG_Load(path.c_str());
            if (!surface) {
                // Handle loading error
                return nullptr;
            }

            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);

            if (!texture) {
                // Handle texture creation error
                return nullptr;
            }

            auto resource = std::make_shared<TextureResource>(texture);
            resources[path] = resource;
            return resource;
        }
    }

    } // AssetMng