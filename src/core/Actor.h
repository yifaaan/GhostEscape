#pragma once

#include "ObjectWorld.h"

class Actor : public ObjectWorld {
   public:
    void Move(float delta_time);

    glm::vec2 velocity() const { return velocity_; }
    void set_velocity(const glm::vec2& v) { velocity_ = v; }

    float max_speed() const { return max_speed_; }
    void set_max_speed(float s) { max_speed_ = s; }

   protected:
    // speed
    glm::vec2 velocity_{};
    // 最大速度大小
    float max_speed_{300.f};
};