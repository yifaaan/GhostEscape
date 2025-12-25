#include "SceneMain.h"
#include "Player.h"

void SceneMain::Init()
{
    world_size_ = game_.screen_size() * 3.0f;
    camera_position_ = world_size_ / 2.f - game_.screen_size() / 2.f;
    player_ = new Player();
    player_->Init();
    player_->set_position(world_size_ / 2.f);
}

void SceneMain::HandleEvents(SDL_Event& event)
{

}

void SceneMain::Update(float delta_time)
{
    // camera_position_ += glm::vec2{10, 10};
    player_->Update(delta_time);
}

void SceneMain::Render()
{
    RenderBackground();
    player_->Render();
}

void SceneMain::Clean()
{
    player_->Clean();
    delete player_;
}

void SceneMain::RenderBackground()
{
    auto start = -camera_position_;
    auto end = world_size_ - camera_position_;
    game_.DrawGrid(start, end, 80.f, {0.5, 0.5, 0.5, 1.0});
    game_.DrawBoundary(start, end, 20.f, {0.5, 0, 0, 1.0});
}