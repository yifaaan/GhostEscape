#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <glm/glm.hpp>
#include <string_view>

class Scene;
class AssetStore;
class Texture;

class Game {
private:
    Game() = default;
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

public:
    ~Game() = default;

    static Game& GetInstance() {
        static Game game;
        return game;
    }

    void Run();
    void Init(std::string_view title, int width, int height);
    void HandleEvents();
    void Update(float delta_time);
    void Render();
    void Clean();

    void DrawGrid(const glm::vec2& top_left, const glm::vec2& bottom_right, float grid_width, SDL_FColor fcolor);
    void DrawBoundary(const glm::vec2& top_left, const glm::vec2& bottom_right, float boundary_width,
                      SDL_FColor fcolor);
    void RenderTexture(const Texture& texture, const glm::vec2& position, const glm::vec2& size);
    void RenderFillCircle(const glm::vec2& position, const glm::vec2& size, float alpha);
    
    glm::vec2 screen_size() const { return screen_size_; }

    Scene* current_scene() { return current_scene_; }

    AssetStore* asset_store() { return asset_store_; }

private:
    glm::vec2 screen_size_{};
    SDL_Window* window_{};
    SDL_Renderer* renderer_{};
    bool is_running_{true};
    // 帧率
    Uint64 fps_{60};
    // 帧延迟 ns 理论
    Uint64 frame_delay_{0};
    // 帧间隔 s 实际
    float delta_time_{0.f};

    Scene* current_scene_{};

    AssetStore* asset_store_{};
};