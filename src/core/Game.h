#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <glm/fwd.hpp>
#include <glm/glm.hpp>

#include <random>
#include <string_view>

class Scene;
class AssetStore;
class Texture;

class Game
{
private:
    Game() = default;
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

public:
    ~Game() = default;

    static Game& GetInstance()
    {
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

    float RandomFloat(float min, float max)
    {
        return std::uniform_real_distribution<float>(min, max)(gen_);
    }

    int RandomInt(int min, int max)
    {
        return std::uniform_int_distribution<>(min, max)(gen_);
    }

    glm::vec2 RandomVec2(const glm::vec2& min, const glm::vec2& max)
    {
        return glm::vec2(RandomFloat(min.x, max.x), RandomFloat(min.y, max.y));
    }

    glm::ivec2 RandomVec2i(const glm::ivec2& min, const glm::ivec2& max)
    {
        return glm::ivec2(RandomInt(min.x, max.x), RandomInt(min.y, max.y));
    }

    glm::vec2 screen_size() const
    {
        return screen_size_;
    }

    Scene* current_scene()
    {
        return current_scene_;
    }

    AssetStore* asset_store()
    {
        return asset_store_;
    }

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
    std::mt19937 gen_{std::random_device{}()};
};