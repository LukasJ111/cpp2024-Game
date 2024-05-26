//
// Created by Acer on 2024-03-17.
//

#ifndef MISKAS_TEXTURERESOURCE_H
#define MISKAS_TEXTURERESOURCE_H


#include <SDL_render.h>
#include "BaseResource.h"

class TextureResource : public ResourceMng::BaseResource{
    private:
        SDL_Texture* texture;
    public:
        explicit TextureResource(SDL_Texture* texture) : texture(texture) {}
        ~TextureResource() override {
            SDL_DestroyTexture(texture);
        }
        [[nodiscard]] SDL_Texture* getTexture() const { return texture; }
};


#endif //MISKAS_TEXTURERESOURCE_H
