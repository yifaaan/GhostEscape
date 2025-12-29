#include "Collider.h"

#include <glm/geometric.hpp>

Collider* Collider::AddColliderChild(ObjectScreen* parent, const glm::vec2& size, Type t) {
    auto collider = new Collider();
    collider->Init();
    collider->set_parent(parent);
    collider->set_size(size);
    collider->set_type(t);
    parent->AddChildren(collider);
    return collider;
}

bool Collider::IsColliding(const Collider& other) const {
    if (!parent_ || !other.parent_) return false;

    const Type typeA = type_;
    const Type typeB = other.type();

    // Case 1: Circle vs Circle
    if (typeA == Type::kCircle && typeB == Type::kCircle) {
        const auto posA = parent_->position() + offset_ + size_ / 2.f;
        const auto posB = other.parent_->position() + other.offset_ + other.size() / 2.f;
        return glm::distance(posA, posB) < (size_.x + other.size().x) / 2.f;
    }
    // TODO: Others
    return false;
}

void Collider::Render() {
#ifdef DEBUG_MODE
    ObjectAffiliate::Render();
    if (!parent_) return;
    auto position = parent_->render_position() + offset_;
    game_.RenderFillCircle(position, size_, 0.2f);
#endif
}
