#include "Player.h"

#include "affiliate/SpriteAnim.h"
#include "core/Scene.h"

void Player::Init() {
    Actor::Init();
    sprite_idle_ = SpriteAnim::AddSpriteAnimChild(this, "assets/sprite/ghost-idle.png", 2.f);
    sprite_move_ = SpriteAnim::AddSpriteAnimChild(this, "assets/sprite/ghost-move.png", 2.f);
    sprite_move_->set_active(false);
}

void Player::HandleEvents(SDL_Event& event) { Actor::HandleEvents(event); }

void Player::Update(float delta_time) {
    Actor::Update(delta_time);
    KeyboardControl();
    CheckState();
    Move(delta_time);
    // 玩家移动的同时，同步相机移动
    SyncCamera();
}

void Player::Render() {
    Actor::Render();
    // game_.DrawBoundary(render_position_, render_position_ + glm::vec2{20.f, 20.f}, 10.f, {1.f, 0.f, 0.f, 1.f});
}

void Player::Clean() { Actor::Clean(); }

void Player::KeyboardControl() {
    // 减速效果
    velocity_ *= 0.9f;

    auto keyboard_state = SDL_GetKeyboardState(nullptr);
    if (keyboard_state[SDL_SCANCODE_W]) {
        velocity_.y = -max_speed_;
    }
    if (keyboard_state[SDL_SCANCODE_S]) {
        velocity_.y = max_speed_;
    }
    if (keyboard_state[SDL_SCANCODE_A]) {
        velocity_.x = -max_speed_;
    }
    if (keyboard_state[SDL_SCANCODE_D]) {
        velocity_.x = max_speed_;
    }
}

void Player::SyncCamera() { game_.current_scene()->set_camera_position(position_ - game_.screen_size() / 2.f); }

void Player::CheckState() {
    if (velocity_.x < 0.f) {
        sprite_move_->set_flip(true);
        sprite_idle_->set_flip(true);
    } else {
        sprite_move_->set_flip(false);
        sprite_idle_->set_flip(false);
    }

    // 动静切换
    bool new_is_moving = glm::length(velocity_) > 0.1f;
    if (new_is_moving != is_moving_) {
        is_moving_ = new_is_moving;
        ChangeState(is_moving_);
    }
}

void Player::ChangeState(bool is_moving) {
    if (is_moving) {
        sprite_idle_->set_active(false);
        sprite_move_->set_active(true);
        sprite_move_->set_current_frame(sprite_idle_->current_frame());
        sprite_move_->set_current_frame(sprite_idle_->frame_timer());
    } else {
        sprite_idle_->set_active(true);
        sprite_move_->set_active(false);
        sprite_idle_->set_current_frame(sprite_idle_->current_frame());
        sprite_idle_->set_current_frame(sprite_idle_->frame_timer());
    }
}