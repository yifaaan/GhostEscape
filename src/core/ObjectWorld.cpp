#include "ObjectWorld.h"

#include "Scene.h"

void ObjectWorld::Update(float delta_time)
{
    ObjectScreen::Update(delta_time);
    // 根据世界坐标更新渲染坐标
    render_position_ = game_.current_scene()->WorldToScreen(position_);
}

void ObjectWorld::set_position(const glm::vec2& position)
{
    position_ = position;
    render_position_ = game_.current_scene()->WorldToScreen(position);
}

void ObjectWorld::set_render_position(const glm::vec2& render_position)
{
    render_position_ = render_position;
    position_ = game_.current_scene()->ScreenToWorld(render_position);
}