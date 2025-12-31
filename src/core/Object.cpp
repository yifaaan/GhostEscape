#include "Object.h"

#include <algorithm>
#include <ranges>

void Object::HandleEvents(SDL_Event& event)
{
    for (auto c : children_to_add_)
    {
        children_.push_back(c);
    }
    children_to_add_.clear();
    for (auto* c : children_ | std::views::filter(&Object::is_active))
    {
        c->HandleEvents(event);
    }
}

void Object::Update(float delta_time)
{
    for (auto c : children_to_add_)
    {
        children_.push_back(c);
    }
    children_to_add_.clear();
    std::erase_if(children_, [](Object* c) {
        if (!c->need_remove())
            return false;
        c->Clean();
        delete c;
        return true;
    });
    for (auto c : children_ | std::views::filter(&Object::is_active))
    {
        c->Update(delta_time);
    }
}
void Object::Render()
{
    for (auto* c : children_ | std::views::filter(&Object::is_active))
    {
        c->Render();
    }
}

void Object::Clean()
{
    std::ranges::for_each(children_, [](auto c) { c->Clean(); });
    children_.clear();
}