#pragma once

#include "core/Scene.h"

class Player;

class SceneMain : public Scene {
   public:
    SceneMain() = default;
    virtual ~SceneMain() = default;

    virtual void Init() override;
    virtual void HandleEvents(SDL_Event& event) override;
    virtual void Update(float delta_time) override;
    virtual void Render() override;
    virtual void Clean() override;

   private:
    void RenderBackground();

    Player* player_{};
};