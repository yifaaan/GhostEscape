#pragma once

#include "Object.h"
#include "ObjectWorld.h"
#include "ObjectScreen.h"

#include <vector>

#include <glm/glm.hpp>

class Scene : public Object
{
public:
    Scene() = default;
    virtual ~Scene() = default;

    void Init() override {};
    void HandleEvents(SDL_Event& event) override;
    void Update(float delta_time) override;
    void Render() override;
    void Clean() override;

    glm::vec2 WorldToScreen(const glm::vec2& world_position) const
    {
        return world_position - camera_position_;
    }

    glm::vec2 ScreenToWorld(const glm::vec2& screen_position) const
    {
        return screen_position + camera_position_;
    }

    glm::vec2 camera_position() const
    {
        return camera_position_;
    }
    void set_camera_position(const glm::vec2& p);

    glm::vec2 world_size() const
    {
        return world_size_;
    }
    void set_world_size(const glm::vec2& s)
    {
        world_size_ = s;
    }

    void AddChildren(Object* object) override;
    void RemoveChildren(Object* object) override;
protected:
    glm::vec2 world_size_{};
    // 相机位置
    glm::vec2 camera_position_{};

    std::vector<ObjectWorld*> children_world_;
    std::vector<ObjectScreen*> children_screen_;
};