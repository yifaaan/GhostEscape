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

    static Sprite* AddSpriteChild(ObjectScreen* parent, const std::string& path, float scale);
    
    Texture texture() const { return texture_; }
    virtual void set_texture(const Texture& t);

    void SetScale(float s) { size_ *= s;}
protected:
    Texture texture_;
};