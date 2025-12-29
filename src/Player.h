#pragma once

#include "affiliate/SpriteAnim.h"
#include "core/Actor.h"

class Player : public Actor {
   public:
    void Init() override;
    void HandleEvents(SDL_Event& event) override;
    void Update(float delta_time) override;
    void Render() override;
    void Clean() override;

    void KeyboardControl();

    void SyncCamera();

    void CheckState();

    void ChangeState(bool is_moving);

   private:
    bool is_moving_{};
    SpriteAnim* sprite_idle_{};
    SpriteAnim* sprite_move_{};
};