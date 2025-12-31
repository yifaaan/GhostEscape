#include "Stats.h"

#include "../core/Actor.h"

void Stats::Update(float delta_time)
{
    Object::Update(delta_time);
    RegenMana(delta_time);
    if (is_invincible_)
    {
        invincible_timer_ += delta_time;
        if (invincible_timer_ > invincible_time_)
        {
            is_invincible_ = false;
            invincible_timer_ = 0.f;
        }
    }
}

bool Stats::CanUseMana(float mana_cost)
{
    return mana_ >= mana_cost;
}

void Stats::UseMana(float mana_cost)
{
    mana_ - mana_cost <= 0.f ? mana_ = 0.f : mana_ -= mana_cost;
}

void Stats::RegenMana(float delta_time)
{
    mana_ += mana_regen_ * delta_time;
    if (mana_ > max_mana_)
    {
        mana_ = max_mana_;
    }
}

void Stats::TakeDamage(float damage)
{
    if (is_invincible_)
    {
        return;
    }
    health_ -= damage;
    if (health_ <= 0.f)
    {
        health_ = 0.f;
        is_alive_ = false;
    }
    SDL_Log("health = %f", health_);
    is_invincible_ = true;
    invincible_timer_ = 0.f;
}

Stats* Stats::AddStatsChild(Actor* parent, float max_health, float max_mana, float damage, float mana_regen)
{
    auto stats = new Stats();
    stats->Init();
    stats->set_parent(parent);
    stats->set_max_health(max_health);
    stats->set_max_mana(max_mana);
    stats->set_damage(damage);
    stats->set_mana_regen(mana_regen);
    parent->AddChildren(stats);
    return stats;
}
