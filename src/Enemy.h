#pragma once

#include "affiliate/SpriteAnim.h"
#include "core/Actor.h"

class Player;
class Collider;

class Enemy : public Actor
{
private:
    enum class State
    {
        kNormal,
        kHurt,
        kDead,
    };

public:
    static Enemy* AddEnemyChild(Object* parent, Player* target, const glm::vec2& position);

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

    void CheckState();
    void ChangeState(State s);

    void Remove();

    void Attack();

private:
    Player* target_{};
    State current_state_{State::kNormal};
    SpriteAnim* anim_normal_{};
    SpriteAnim* anim_hurt_{};
    SpriteAnim* anim_dead_{};
    SpriteAnim* current_anim_{};
    Collider* collider_{};
};