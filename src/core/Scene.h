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

protected:
    // 相机位置
    glm::vec2 camera_position_{};
    // 场景的物体
    std::vector<Object*> objects_;
};