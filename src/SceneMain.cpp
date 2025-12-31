#include "SceneMain.h"

#include "Enemy.h"
#include "Player.h"
#include "Spawner.h"
#include "screen/UIMouse.h"

void SceneMain::Init()
{
    Scene::Init();
    SDL_HideCursor();
    world_size_ = game_.screen_size() * 3.0f;
    camera_position_ = world_size_ / 2.f - game_.screen_size() / 2.f;

    player_ = new Player();
    player_->Init();
    player_->set_position(world_size_ / 2.f);
    AddChildren(player_);

    // auto enemy = new Enemy();
    // enemy->Init();
    // enemy->set_position(world_size_ / 3.f);
    // enemy->set_target(player_);
    // Effect::AddEffectChild(this, "assets/effect/184_3.png", world_size_ / 3.f, 1.f, enemy);
    spawner_ = new Spawner();
    spawner_->Init();
    spawner_->set_target(player_);
    AddChildren(spawner_);
    ui_mouse_ = UIMouse::AddUIMouseChild(this, "assets/UI/mouse1.png", "assets/UI/mouse2.png", 0.5f, Anchar::kCenter);
}

void SceneMain::HandleEvents(SDL_Event& event)
{
    Scene::HandleEvents(event);
}

void SceneMain::Update(float delta_time)
{
    Scene::Update(delta_time);
    // camera_position_ += glm::vec2{10, 10};
}

void SceneMain::Render()
{
    RenderBackground();
    Scene::Render();
}

void SceneMain::Clean()
{
    Scene::Clean();
}

void SceneMain::RenderBackground()
{
    auto start = -camera_position_;
    auto end = world_size_ - camera_position_;
    game_.DrawGrid(start, end, 80.f, {0.5, 0.5, 0.5, 1.0});
    game_.DrawBoundary(start, end, 20.f, {0.5, 0, 0, 1.0});
}