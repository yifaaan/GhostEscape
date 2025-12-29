#pragma once

#include "../core/ObjectAffiliate.h"

class Collider : public ObjectAffiliate {
public:
    enum class Type {
        kCircle,  // size_.x 表示直径, size_.y=x
        kRect,
    };

    static Collider* AddColliderChild(ObjectScreen* parent, const glm::vec2& size, Type t);

    bool IsColliding(const Collider& other) const;

    void Render() override;

    Type type() const { return type_; }
    void set_type(Type t) { type_ = t; }

protected:
    Type type_{Type::kCircle};
};