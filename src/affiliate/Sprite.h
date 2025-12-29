#pragma once

#include <SDL3/SDL_render.h>

#include <string>

#include "../core/ObjectAffiliate.h"

struct Texture {
    SDL_Texture* texture{};
    SDL_FRect src_rect{};
    float angle{};
    bool flip{};

    Texture() = default;
    explicit Texture(const std::string& path);
};

class Sprite : public ObjectAffiliate {
   public:
    void Render() override;

    static Sprite* AddSpriteChild(ObjectScreen* parent, const std::string& path, float scale);

    Texture texture() const { return texture_; }
    virtual void set_texture(const Texture& t);

    void SetScale(float s) { size_ *= s; }

    bool flip() const { return texture_.flip; }
    void set_flip(bool f) { texture_.flip = f; }

    float angle() const { return texture_.angle; }
    void set_angle(float a) { texture_.angle = a; }

    bool is_finished() const { return is_finished_; }
    void set_finished(bool f) { is_finished_ = f; }

   protected:
    Texture texture_;
    bool is_finished_{};
};