#include "Actor.h"

#include "Scene.h"
#include "../raw/Stats.h"

void Actor::Move(float delta_time)
{
    set_position(position_ + velocity_ * delta_time);
    // 限制player移动范围为world
    set_position(glm::clamp(position_, glm::vec2{}, game_.current_scene()->world_size()));
}

void Actor::TakeDamage(float damage)
{
    if (!stats_)
    {
        return;
    }
    stats_->TakeDamage(damage);
}

bool Actor::IsAlive()
{
    if (!stats_)
    {
        return false;
    }
    return stats_->is_alive();
}