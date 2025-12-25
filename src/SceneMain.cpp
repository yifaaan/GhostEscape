#include "SceneMain.h"

void SceneMain::Init()
{
    word_size_ = game_.screen_size() * 3.0f;
}

void SceneMain::HandleEvents(SDL_Event& event)
{

}

void SceneMain::Update(float delta_time)
{
    camera_position_ += glm::vec2{2, 2};
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
}