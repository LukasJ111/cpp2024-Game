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
        AssetManager(SDL_Renderer* renderer);

        std::shared_ptr<TextureResource> loadTexture(const std::string& path);

    };

} // namespace ResourceMng

#endif //MISKAS_ASSETMANAGER_H
