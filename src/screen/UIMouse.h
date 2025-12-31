#pragma once

#include "../core/ObjectScreen.h"

class Sprite;

class UIMouse : public ObjectScreen
{
public:
    static UIMouse* AddUIMouseChild(Object* parent, const std::string& path1, const std::string& path2, float scale, Anchar anchar);

    void Update(float delta_time) override;

private:
    Sprite* sprite1_{};
    Sprite* sprite2_{};
    float timer_{};
};