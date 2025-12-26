#pragma once

#include "Game.h"
#include "Defs.h"

#include <vector>
#include <algorithm>

class Object
{
public:
    // 子类的构造和虚构必须为空
    Object() = default;
    virtual ~Object() = default;

    virtual void Init() {};
    virtual void HandleEvents(SDL_Event& event);
    virtual void Update(float delta_time);
    virtual void Render();
    virtual void Clean();

    virtual void AddChildren(Object* object) { children_.push_back(object); }
    virtual void RemoveChildren(Object* object) { children_.erase(std::remove(children_.begin(), children_.end(), object), children_.end()); }

    ObjectType type() const { return type_; }
    void set_type(ObjectType t) { type_ = t; }

    void set_active(bool a) { is_active_ = a; }
    bool is_active() const { return is_active_; }
    
protected:
    Game& game_ = Game::GetInstance();
    std::vector<Object*> children_;
    ObjectType type_{ObjectType::kNone};
    bool is_active_{true};
};