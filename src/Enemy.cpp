#include "Enemy.h"

#include "Player.h"
#include "affiliate/SpriteAnim.h"

void Enemy::Init()
{
    Actor::Init();
    SpriteAnim::AddSpriteAnimChild(this, "assets/sprite/ghost-Sheet.png", 2.0f);
}

void Enemy::Update(float delta_time)
{
    Actor::Update(delta_time);
    AimTarget(target_);
    Move(delta_time);
}

void Enemy::AimTarget(Player* p)
{
    if (!p)
    {
        return;
    }
    auto direction = p->position() - position_;
    direction = glm::normalize(direction);
    velocity_ = direction * max_speed_;
}