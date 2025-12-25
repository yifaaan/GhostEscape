#pragma once

#include "core/Actor.h"

class Player : public Actor
{
public:
    void Init() override;
    void HandleEvents(SDL_Event& event) override;
    void Update(float delta_time) override;
    void Render() override;
    void Clean() override;

    void KeyboardControl();

    void Move(float delta_time);

    void SyncCamera();
};