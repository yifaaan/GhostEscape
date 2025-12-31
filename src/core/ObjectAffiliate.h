#pragma once

#include "Defs.h"
#include "ObjectScreen.h"

class ObjectAffiliate : public Object
{
public:
    ObjectScreen* parent()
    {
        return parent_;
    }
    void set_parent(ObjectScreen* p)
    {
        parent_ = p;
    }

    glm::vec2 offset() const
    {
        return offset_;
    }
    void set_offset(const glm::vec2& o)
    {
        offset_ = o;
    }

    glm::vec2 size() const
    {
        return size_;
    }
    void set_size(const glm::vec2& s);

    void SetScale(float s);

    void SetOffsetByAnchar(Anchar a);

    Anchar anchar() const
    {
        return anchar_;
    }
    void set_anchar(Anchar a)
    {
        anchar_ = a;
    }
protected:
    ObjectScreen* parent_{};
    // 相对parent的
    glm::vec2 offset_{};
    glm::vec2 size_{};
    Anchar anchar_{Anchar::kCenter};
};