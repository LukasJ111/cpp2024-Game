//
// Created by Acer on 2024-03-17.
//

#ifndef MISKAS_ASSETMANAGER_H
#define MISKAS_ASSETMANAGER_H

#include <string>
#include <memory>
#include <SDL_render.h>
#include <unordered_map>
#include "BaseResource.h"
#include <SDL_image.h>

namespace ResourceMng {

    class AssetManager {
    private:
        SDL_Renderer* renderer;
        std::unordered_map<std::string, std::shared_ptr<BaseResource>> resources;

    public:
        AssetManager(SDL_Renderer* renderer) : renderer(renderer) {}

        std::shared_ptr<TextureResource> loadTexture(const std::string& path) {
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

    };

} // namespace ResourceMng

#endif //MISKAS_ASSETMANAGER_H
