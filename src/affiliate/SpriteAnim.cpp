#include "SpriteAnim.h"

void SpriteAnim::Update(float delta_time) {
    if (is_finished_) {
        return;
    }
    Sprite::Update(delta_time);
    frame_timer_ += delta_time;
    if (frame_timer_ > 1.f / fps_) {
        current_frame_++;
        if (current_frame_ >= total_frame_) {
            current_frame_ = 0;
            if (!is_loop_) {
                is_finished_ = true;
            }
        }
        frame_timer_ = 0.f;
    }
    texture_.src_rect.x = current_frame_ * texture_.src_rect.w;
}

SpriteAnim* SpriteAnim::AddSpriteAnimChild(ObjectScreen* parent, const std::string& path, float scale) {
    auto sprite_anim = new SpriteAnim();
    sprite_anim->Init();
    sprite_anim->set_parent(parent);
    sprite_anim->set_texture(Texture{path});
    sprite_anim->SetScale(scale);
    parent->AddChildren(sprite_anim);
    return sprite_anim;
}

void SpriteAnim::set_texture(const Texture& t) {
    texture_ = t;
    // 假设每帧是正方形（宽度 = 高度）
    total_frame_ = static_cast<int>(t.src_rect.w) / static_cast<int>(t.src_rect.h);
    // 单帧宽度 = 高度
    texture_.src_rect.w = t.src_rect.h;
    size_ = glm::vec2{texture_.src_rect.w, texture_.src_rect.h};
}