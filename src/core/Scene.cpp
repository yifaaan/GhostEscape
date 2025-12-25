#include "Scene.h"

void Scene::set_camera_position(const glm::vec2& p)
{
    camera_position_ = p;
    // 限制相机移动范围
    camera_position_ = glm::clamp(camera_position_, glm::vec2{} - 100.f, world_size_ + 100.f);
}