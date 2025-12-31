#pragma once

#include "../affiliate/SpriteAnim.h"
#include "../core/ObjectWorld.h"

class Effect : public ObjectWorld
{
public:
    void Update(float delta_time) override;

    static Effect* AddEffectChild(Object* parent, const std::string& path, const glm::vec2& position,float scale, ObjectWorld* next_object);

    SpriteAnim* sprite() const
    {
        return sprite_;
    }
    void set_sprite(SpriteAnim* s)
    {
        sprite_ = s;
    }
    ObjectWorld* next_object() const
    {
        return next_object_;
    }
    void set_next_object(ObjectWorld* o)
    {
        next_object_ = o;
    }

private:
    void CheckFinish();

    SpriteAnim* sprite_{};
    ObjectWorld* next_object_{};
};