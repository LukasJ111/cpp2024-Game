//
// Created by Acer on 2024-03-17.
//

#ifndef MISKAS_BASERESOURCE_H
#define MISKAS_BASERESOURCE_H

#include <SDL_render.h>

namespace ResourceMng {

    class BaseResource {
    public:
        virtual ~BaseResource() {}
    };

    class TextureResource : public BaseResource {
    private:
        SDL_Texture* texture;
    public:
        TextureResource(SDL_Texture* texture) : texture(texture) {}
        ~TextureResource() {
            SDL_DestroyTexture(texture);
        }
        SDL_Texture* getTexture() const { return texture; }
    };

} // namespace ResourceMng

#endif //MISKAS_BASERESOURCE_H
