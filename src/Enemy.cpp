#include "Enemy.h"

#include "Player.h"
#include "affiliate/SpriteAnim.h"
#include "core/Scene.h"

void Enemy::Init() {
    Actor::Init();
    anim_normal_ = SpriteAnim::AddSpriteAnimChild(this, "assets/sprite/ghost-Sheet.png", 2.0f);
    anim_hurt_ = SpriteAnim::AddSpriteAnimChild(this, "assets/sprite/ghostHurt-Sheet.png", 2.0f);
    anim_dead_ = SpriteAnim::AddSpriteAnimChild(this, "assets/sprite/ghostDead-Sheet.png", 2.0f);
    anim_hurt_->set_active(false);
    anim_dead_->set_active(false);
    anim_dead_->set_loop(false);
    current_anim_ = anim_normal_;
}

void Enemy::Update(float delta_time) {
    Actor::Update(delta_time);
    AimTarget(target_);
    Move(delta_time);
    timer_ += delta_time;
    if (timer_ > 2.f && timer_ < 4.f) {
        ChangeState(State::kHurt);
    } else if (timer_ > 4.f) {
        timer_ = 0.f;
        ChangeState(State::kDead);
    }
    Remove();
}

void Enemy::AimTarget(Player* p) {
    if (!p) {
        return;
    }
    auto direction = p->position() - position_;
    direction = glm::normalize(direction);
    velocity_ = direction * max_speed_;
}

void Enemy::CheckState() {
    // TODO:
}

void Enemy::ChangeState(State s) {
    if (s == current_state_) {
        return;
    }
    current_anim_->set_active(false);
    switch (s) {
        case State::kNormal:
            current_anim_ = anim_normal_;
            break;
        case State::kHurt:
            current_anim_ = anim_hurt_;
            break;
        case State::kDead:
            current_anim_ = anim_dead_;
            break;
    }
    current_anim_->set_active(true);
    current_state_ = s;
}

void Enemy::Remove() {
    if (anim_dead_->is_finished()) {
        need_remove_ = true;
    }
}