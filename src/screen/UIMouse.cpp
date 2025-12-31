#include "UIMouse.h"

#include "../affiliate/Sprite.h"

UIMouse* UIMouse::AddUIMouseChild(Object* parent, const std::string& path1, const std::string& path2, float scale, Anchar anchar)
{
    auto ui_mouse = new UIMouse();
    ui_mouse->Init();
    ui_mouse->sprite1_ = Sprite::AddSpriteChild(ui_mouse, path1, scale, anchar);
    ui_mouse->sprite2_ = Sprite::AddSpriteChild(ui_mouse, path2, scale, anchar);
    if (parent)
    {
        parent->AddChildren(ui_mouse);
    }
    return ui_mouse;
}


void UIMouse::Update(float delta_time)
{
    ObjectScreen::Update(delta_time);
    timer_ += delta_time;
    if (timer_ < 0.3f)
    {
        sprite1_->set_active(true);
        sprite2_->set_active(false);
    }
    else if (timer_ < 0.6f)
    {
        sprite1_->set_active(false);
        sprite2_->set_active(true);
    }
    else
    {
        timer_ = 0.f;
        sprite1_->set_active(false);
        sprite2_->set_active(false);
    }
    set_render_position(game_.mouse_position());
}