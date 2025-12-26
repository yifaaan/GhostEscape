#pragma once

#include "Defs.h"
#include "ObjectScreen.h"

class ObjectWorld : public ObjectScreen
{
public:
    void Init() override { type_ = ObjectType::kObjectWrold; }
    
    void Update(float delta_time) override;

    glm::vec2 position() const
    {
        return position_;
    }

    void set_position(const glm::vec2& position);
    
    void set_render_position(const glm::vec2& render_position) override;

protected:
    // 含义： 对象在游戏世界中的实际位置
    //
    // 坐标系： 世界空间，独立于屏幕
    //
    // 特点： 真实位置，会随摄像机移动而改变在屏幕上的显示位置
    glm::vec2 position_{};
};