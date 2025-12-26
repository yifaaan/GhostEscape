#pragma once

#include "Defs.h"
#include "Object.h"

class ObjectScreen : public Object
{
public:
    void Init() override { type_ = ObjectType::kObjectScreen; }

    glm::vec2 render_position() const
    {
        return render_position_;
    }

    virtual void set_render_position(const glm::vec2& render_position)
    {
        render_position_ = render_position;
    }

protected:
    // 含义： 对象在屏幕上的像素位置
    //
    // 坐标系： 屏幕左上角为 (0, 0)，右下角为 (1280, 720)
    //
    // 特点： 固定在屏幕上，不受摄像机影响
    glm::vec2 render_position_{};
};