#include "SceneMain.h"

void SceneMain::Init()
{
    word_size_ = game_.screen_size() * 3.0f;
    camera_position_ = {-200.f, -200.f};
}

void SceneMain::HandleEvents(SDL_Event& event)
{

}

void SceneMain::Update(float delta_time)
{
    camera_position_ += glm::vec2{10, 10};
}

void SceneMain::Render()
{
    RenderBackground();
}

void SceneMain::Clean()
{

}

void SceneMain::RenderBackground()
{
    auto start = -camera_position_;
    auto end = word_size_ - camera_position_;
    game_.DrawGrid(start, end, 80.f, {0.5, 0.5, 0.5, 1.0});
    game_.DrawBoundary(start, end, 20.f, {0.5, 0, 0, 1.0});
}