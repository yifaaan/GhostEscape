#include "Effect.h"

#include "../core/Scene.h"

void Effect::Update(float delta_time)
{
    ObjectWorld::Update(delta_time);
    CheckFinish();
}

Effect* Effect::AddEffectChild(Object* parent, const std::string& path, const glm::vec2& position,float scale, ObjectWorld* next_object)
{
    auto effect = new Effect();
    effect->Init();
    effect->sprite_ = SpriteAnim::AddSpriteAnimChild(effect, path, scale, Anchar::kCenter);
    effect->sprite_->set_loop(false);
    effect->set_position(position);
    effect->set_next_object(next_object);
    parent->SafeAddChildren(effect);
    return effect;
}


void Effect::CheckFinish()
{
    if (sprite_->is_finished())
    {
        need_remove_ = true;
        if (next_object_)
        {
            // 如果 child->Update() 内部触发了逻辑（比如生成特效），
            // 调用了 parent->AddChildren()，就会直接向 children_ 插入新元素。
            game_.current_scene()->AddChildren(next_object_);
        }
    }
}
