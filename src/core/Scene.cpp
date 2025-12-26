#include "Scene.h"
#include "Defs.h"

#include <algorithm>
#include <ranges>

void Scene::HandleEvents(SDL_Event& event)
{
    Object::HandleEvents(event);
    // 先处理screen事件
    std::ranges::for_each(children_screen_, [&event](auto o)
    {
        if (!o->is_active())
        {
            return;
        }
        o->HandleEvents(event);
    });
    std::ranges::for_each(children_world_, [&event](auto o)
    {
        if (!o->is_active())
        {
            return;
        }
        o->HandleEvents(event);
    });
}

void Scene::Update(float delta_time)
{
    Object::Update(delta_time);
    // 先更新世界物体的逻辑
    std::ranges::for_each(children_world_, [delta_time](auto o)
    {
        if (!o->is_active())
        {
            return;
        }
        o->Update(delta_time);
    });
    std::ranges::for_each(children_screen_, [delta_time](auto o)
    {
        if (!o->is_active())
        {
            return;
        }
        o->Update(delta_time);
    });
}

void Scene::Render()
{
    Object::Render();
    std::ranges::for_each(children_world_, [](auto o)
    {
        if (!o->is_active())
        {
            return;
        }
        o->Render();
    });
    std::ranges::for_each(children_screen_, [](auto o)
    {
        if (!o->is_active())
        {
            return;
        }
        o->Render();
    });
}

void Scene::Clean()
{
    Object::Clean();
    std::ranges::for_each(children_world_, [](auto o)
    {
        o->Clean();
    });
    children_world_.clear();
    std::ranges::for_each(children_screen_, [](auto o)
    {
        o->Clean();
    });
    children_screen_.clear();
}

void Scene::set_camera_position(const glm::vec2& p)
{
    camera_position_ = p;
    // 限制相机移动范围
    camera_position_ = glm::clamp(camera_position_, glm::vec2{} - 100.f, world_size_ + 100.f);
}

void Scene::AddChildren(Object* object)
{
    switch (object->type())
    {
    case ObjectType::kObjectWrold:
        children_world_.push_back(dynamic_cast<ObjectWorld*>(object));
        break;
    case ObjectType::kObjectScreen:
        children_screen_.push_back(dynamic_cast<ObjectScreen*>(object));
        break;
    default:
        children_.push_back(object);
        break;
    }
}

void Scene::RemoveChildren(Object* object)
{
    switch (object->type())
    {
    case ObjectType::kObjectWrold:
        children_world_.erase(std::remove(children_world_.begin(), children_world_.end(), object), children_world_.end());
        break;
    case ObjectType::kObjectScreen:
        children_screen_.erase(std::remove(children_screen_.begin(), children_screen_.end(), object), children_screen_.end());
        break;
    default:
        children_.erase(std::remove(children_.begin(), children_.end(), object), children_.end());
        break;
    }
}