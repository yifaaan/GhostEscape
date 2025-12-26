#include "Sprite.h"

#include "../core/AssetStore.h"

Texture::Texture(const std::string& path)
{
    texture = Game::GetInstance().asset_store()->texture(path);
    SDL_GetTextureSize(texture, &src_rect.w, &src_rect.h);
}

void Sprite::Render()
{
    ObjectAffiliate::Render();
    if (!texture_.texture || !parent_)
    {
        return;
    }
    auto p = parent_->render_position() + offset_;
    game_.RenderTexture(texture_, p, size_);
}

void Sprite::set_texture(const Texture& t)
{
    texture_ = t;
    size_ = glm::vec2{texture_.src_rect.w, texture_.src_rect.h};
}
