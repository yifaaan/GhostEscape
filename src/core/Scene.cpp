#include "Scene.h"

#include <algorithm>
#include <ranges>

#include "Defs.h"

void Scene::HandleEvents(SDL_Event& event) {
    Object::HandleEvents(event);

    for (auto* o : children_screen_ | std::views::filter(&Object::is_active)) {
        o->HandleEvents(event);
    }

    for (auto* o : children_world_ | std::views::filter(&Object::is_active)) {
        o->HandleEvents(event);
    }
}

void Scene::Update(float delta_time) {
    Object::Update(delta_time);

    std::erase_if(children_world_, [](Object* o) {
        if (!o->need_remove()) return false;
        o->Clean();
        delete o;
        SDL_Log("Scene: remove world children: %p", o);
        return true;
    });
    for (auto* o : children_world_ | std::views::filter(&Object::is_active)) {
        o->Update(delta_time);
    }

    std::erase_if(children_screen_, [](Object* o) {
        if (!o->need_remove()) return false;
        o->Clean();
        delete o;
        return true;
    });
    for (auto* o : children_screen_ | std::views::filter(&Object::is_active)) {
        o->Update(delta_time);
    }
}

void Scene::Render() {
    Object::Render();

    for (auto* o : children_world_ | std::views::filter(&Object::is_active)) {
        o->Render();
    }

    for (auto* o : children_screen_ | std::views::filter(&Object::is_active)) {
        o->Render();
    }
}

void Scene::Clean() {
    Object::Clean();
    std::ranges::for_each(children_world_, &Object::Clean);
    children_world_.clear();
    std::ranges::for_each(children_screen_, &Object::Clean);
    children_screen_.clear();
}

void Scene::set_camera_position(const glm::vec2& p) {
    camera_position_ = p;
    // 限制相机移动范围
    camera_position_ = glm::clamp(camera_position_, glm::vec2{} - 100.f, world_size_ + 100.f);
}

void Scene::AddChildren(Object* object) {
    switch (object->type()) {
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

void Scene::RemoveChildren(Object* object) {
    switch (object->type()) {
        case ObjectType::kObjectWrold:
            std::erase(children_world_, dynamic_cast<ObjectWorld*>(object));
            break;
        case ObjectType::kObjectScreen:
            std::erase(children_screen_, dynamic_cast<ObjectScreen*>(object));
            break;
        default:
            std::erase(children_, object);
            break;
    }
}