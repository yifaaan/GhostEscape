#include "Player.h"

#include "core/Scene.h"

void Player::Init()
{

}

void Player::HandleEvents(SDL_Event& event)
{
    
}

void Player::Update(float delta_time)
{
    KeyboardControl();
    Move(delta_time);
    // 玩家移动的同时，同步相机移动
    SyncCamera();
}

void Player::Render()
{
    game_.DrawBoundary(render_position_, render_position_ + glm::vec2{20.f, 20.f}, 10.f, {1.f, 0.f, 0.f, 1.f});
}

void Player::Clean()        
{
     
}

void Player::KeyboardControl()
{
    // 减速效果
    velocity_ *= 0.9f;

    auto keyboard_state = SDL_GetKeyboardState(nullptr);
    if (keyboard_state[SDL_SCANCODE_W])
    {
        velocity_.y = -max_speed_;
    }
    if (keyboard_state[SDL_SCANCODE_S])
    {
        velocity_.y = max_speed_;
    }
    if (keyboard_state[SDL_SCANCODE_A])
    {
        velocity_.x = -max_speed_;
    }
    if (keyboard_state[SDL_SCANCODE_D])
    {
        velocity_.x = max_speed_;
    }
}

void Player::Move(float delta_time)
{
    set_position(position_ + velocity_ * delta_time);
    // 限制player移动范围为world
    set_position(glm::clamp(position_, glm::vec2{}, game_.current_scene()->world_size()));
}

void Player::SyncCamera()
{
    game_.current_scene()->set_camera_position(position_ - game_.screen_size() / 2.f);
}