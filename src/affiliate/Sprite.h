#pragma once

#include "../core/ObjectAffiliate.h"

#include <string>

#include <SDL3/SDL_render.h>


struct Texture
{
    SDL_Texture* texture{};
    SDL_FRect src_rect{};
    float angle{};
    bool flip{};

    Texture() = default;
    explicit Texture(const std::string& path);
};

class Sprite : public ObjectAffiliate
{
public:
    void Render() override;

    Texture texture() const { return texture_; }
    void set_texture(const Texture& t);
protected:
    Texture texture_;
};