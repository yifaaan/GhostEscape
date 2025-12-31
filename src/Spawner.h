#pragma once

#include "core/Object.h"

class Player;

class Spawner : public Object
{
public:
    void Update(float delta_time) override;


    int num() const
    {
        return num_;
    }
    void set_num(int n)
    {
        num_ = n;
    }
    float timer() const
    {
        return timer_;
    }
    void set_timer(float t)
    {
        timer_ = t;
    }

    float interval() const
    {
        return interval_;
    }
    void set_interval(float i)
    {
        interval_ = i;
    }
    Player* target() const
    {
        return target_;
    }
    void set_target(Player* t)
    {
        target_ = t;
    }


protected:
    int num_{20};
    float timer_{};
    float interval_{3.f};
    Player* target_{};
};