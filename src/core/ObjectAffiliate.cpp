#include "ObjectAffiliate.h"
#include "Defs.h"

void ObjectAffiliate::set_size(const glm::vec2& s)
{
    size_ = s;
    SetOffsetByAnchar(anchar_);
}

void ObjectAffiliate::SetScale(float s)
{
    size_ *= s;
    SetOffsetByAnchar(anchar_);
}

void ObjectAffiliate::SetOffsetByAnchar(Anchar a)
{
    anchar_ = a;
    switch (anchar_)
    {
        case Anchar::kTopLeft:
            offset_ = glm::vec2{};
            break;
        case Anchar::kTopCenter:
            offset_ = glm::vec2{-size_.x / 2.f, 0.f};
            break;
        case Anchar::kTopRight:
            offset_ = glm::vec2{-size_.x, 0.f};
            break;
        case Anchar::kCenterLeft:
            offset_ = glm::vec2{0.f, -size_.y / 2.f};
            break;
        case Anchar::kCenter:
            offset_ = glm::vec2{-size_.x / 2.f, -size_.y / 2.f};
            break;
        case Anchar::kCenterRight:
            offset_ = glm::vec2{0.f, -size_.y / 2.f};
            break;
        case Anchar::kBottomLeft:
            offset_ = glm::vec2{0.f, -size_.y};
            break;
        case Anchar::kBottomCenter:
            offset_ = glm::vec2{-size_.x / 2.f, -size_.y};
            break;
        case Anchar::kBottomRight:
            offset_ = glm::vec2{-size_.x, -size_.y};
            break;
        default:
            break;
    }
}