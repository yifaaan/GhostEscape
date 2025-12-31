#include "Spawner.h"

#include "Enemy.h"
#include "world/Effect.h"
#include "core/Scene.h"
#include "Player.h"

void Spawner::Update(float delta_time)
{
    if (!target_ || !target_->IsAlive())
    {
        return;
    }
    Object::Update(delta_time);
    timer_ += delta_time;
    if (timer_ >= interval_)
    {
        timer_ = 0.f;
        for (int i = 0; i < num_; i++)
        {
            auto pos = game_.RandomVec2(game_.current_scene()->camera_position(), game_.current_scene()->camera_position() + game_.screen_size());
            auto enemy = Enemy::AddEnemyChild(nullptr, target_, pos);
            Effect::AddEffectChild(game_.current_scene(), "assets/effect/184_3.png", pos, 1.f, enemy);
        }
    }
}