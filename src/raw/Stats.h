#pragma once

#include "../core/Object.h"

class Actor;

class Stats : public Object
{
public:

    void Update(float delta_time) override;

    bool CanUseMana(float mana_cost);

    void UseMana(float mana_cost);

    void RegenMana(float delta_time);

    void TakeDamage(float damage);


    static Stats* AddStatsChild(Actor* parent, float max_health, float max_mana, float damage, float mana_regen);

    float health() const
    {
        return health_;
    }
    
    void set_health(float health)
    {
        health_ = health;
    }

    float max_health() const
    {
        return max_health_;
    }

    void set_max_health(float max_health)
    {
        max_health_ = max_health;
    }

    float mana() const
    {
        return mana_;
    }

    void set_mana(float mana)
    {
        mana_ = mana;
    }

    float max_mana() const
    {
        return max_mana_;
    }

    void set_max_mana(float max_mana)
    {
        max_mana_ = max_mana;
    }

    float damage() const
    {
        return damage_;
    }

    void set_damage(float damage)
    {
        damage_ = damage;
    }

    bool is_alive() const
    {
        return is_alive_;
    }

    void set_is_alive(bool is_alive)
    {
        is_alive_ = is_alive;
    }

    Actor* parent()
    {
        return parent_;
    }

    void set_parent(Actor* parent)
    {
        parent_ = parent;
    }

    bool is_invincible() const
    {
        return is_invincible_;
    }

    void set_invincible(bool is_invincible)
    {
        is_invincible_ = is_invincible;
    }

    float mana_regen() const
    {
        return mana_regen_;
    }
    void set_mana_regen(float mana_regen)
    {
        mana_regen_ = mana_regen;
    }

protected:
    float health_{100.f};
    float max_health_{100.f};
    float mana_{100.f};
    float max_mana_{100.f};
    float mana_regen_{10.f};
    float damage_{30.f};
    bool is_alive_{true};
    Actor* parent_{};
    bool is_invincible_{};
    float invincible_time_{1.5f};
    float invincible_timer_{0.f};
};