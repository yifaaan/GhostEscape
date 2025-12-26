#include "Object.h"

#include <algorithm>
#include <ranges>

void Object::HandleEvents(SDL_Event& event)
{
    std::ranges::for_each(children_, [&event](auto c)
    {
        if (!c->is_active())
        {
            return;
        }
        c->HandleEvents(event);
    });
}

void Object::Update(float delta_time)
{
    std::ranges::for_each(children_, [delta_time](auto c)
    {
        if (!c->is_active())
        {
            return;
        }
        c->Update(delta_time);
    });
}
void Object::Render()
{
    std::ranges::for_each(children_, [](auto c)
    {
        if (!c->is_active())
        {
            return;
        }
        c->Render();
    });
}

void Object::Clean()
{
    std::ranges::for_each(children_, [](auto c)
    {
        c->Clean();
    });
    children_.clear();
}