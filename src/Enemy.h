#pragma once

#include "core/Actor.h"

class Player;

class Enemy : public Actor
{
public:
    void Init() override;
    
    void Update(float delta_time) override;

    Player* target() const
    {
        return target_;
    }
    void set_target(Player* t)
    {
        target_ = t;
    }

    void AimTarget(Player* p);

private:
    Player* target_{};
};