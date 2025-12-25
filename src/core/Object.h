#pragma once

#include "Game.h"

class Object
{
public:
    // 子类的构造和虚构必须为空
    Object() = default;
    virtual ~Object() = default;

    virtual void Init() {};
    virtual void HandleEvents(SDL_Event& event) {};
    virtual void Update(float delta_time) {};
    virtual void Render() {};
    virtual void Clean() {};

protected:
    Game& game_ = Game::GetInstance();
};