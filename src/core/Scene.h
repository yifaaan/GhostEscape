#pragma once

#include "Object.h"

#include <vector>

#include <glm/glm.hpp>

class Scene : public Object
{
public:
    Scene() = default;
    virtual ~Scene() = default;

    virtual void Init() override {};
    virtual void HandleEvents(SDL_Event& event) override {};
    virtual void Update(float delta_time) override {};
    virtual void Render() override {};
    virtual void Clean() override {};

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
protected:
    glm::vec2 world_size_{};
    // 相机位置
    glm::vec2 camera_position_{};
    // 场景的物体
    std::vector<Object*> objects_;
};