#include "Game.h"

#include "../SceneMain.h"
#include "../affiliate/Sprite.h"
#include "AssetStore.h"

void Game::Run()
{
    while (is_running_)
    {
        auto start = SDL_GetTicksNS();
        HandleEvents();
        Update(delta_time_);
        Render();
        auto end = SDL_GetTicksNS();
        auto elapsed = end - start;
        if (elapsed < frame_delay_)
        {
            SDL_DelayNS(frame_delay_ - elapsed);
            delta_time_ = frame_delay_ / 1.0e9;
        }
        else
        {
            delta_time_ = elapsed / 1.0e9;
        }
        // SDL_Log("frame_delay_: %f, FPS: %f", frame_delay_ / 1.0e9  * 60, 1.0 / delta_time_);
    }
}

void Game::Init(std::string_view title, int width, int height)
{
    screen_size_ = glm::vec2{width, height};

    SDL_Log("Initializing SDL...");
    if (!SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init Error: %s", SDL_GetError());
        is_running_ = false;
        return;
    }
    SDL_Log("SDL initialized successfully");

    SDL_Log("Initializing SDL_mixer...");
    if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) != (MIX_INIT_MP3 | MIX_INIT_OGG))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Mix_Init Error: %s", SDL_GetError());
    }
    if (!Mix_OpenAudio(0, nullptr))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Mix_OpenAudio Error: %s", SDL_GetError());
    }
    // 分配同时播放16个音效的通道
    Mix_AllocateChannels(16);
    Mix_VolumeMusic(MIX_MAX_VOLUME / 4);
    Mix_Volume(-1, MIX_MAX_VOLUME / 4);

    SDL_Log("Initializing SDL_ttf...");
    if (!TTF_Init())
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "TTF_Init Error: %s", SDL_GetError());
    }

    SDL_Log("Creating window and renderer...");
    if (!SDL_CreateWindowAndRenderer(title.data(), width, height, SDL_WINDOW_RESIZABLE, &window_, &renderer_))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateWindowAndRenderer Error: %s", SDL_GetError());
        is_running_ = false;
        return;
    }
    SDL_Log("Window and renderer created successfully");

    SDL_SetRenderLogicalPresentation(renderer_, width, height, SDL_LOGICAL_PRESENTATION_LETTERBOX);
    SDL_Log("Initialization complete");

    frame_delay_ = 1000000000 / fps_;

    // Load assets
    asset_store_ = new AssetStore(renderer_);

    // 创建场景
    current_scene_ = new SceneMain();
    current_scene_->Init();
}

void Game::HandleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_EVENT_QUIT:
            is_running_ = false;
            break;
        default:
            current_scene_->HandleEvents(event);
        }
    }
}

void Game::Update(float delta_time)
{
    mouse_button_flags_ =  SDL_GetMouseState(&mouse_position_.x, &mouse_position_.y);
    current_scene_->Update(delta_time);
}

void Game::Render()
{
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
    SDL_RenderClear(renderer_);
    // DrawGrid({0, 0}, {screen_size_.x, screen_size_.y}, 50, {255, 255, 255, 255});
    current_scene_->Render();
    SDL_RenderPresent(renderer_);
}

void Game::Clean()
{
    if (current_scene_)
    {
        current_scene_->Clean();
        delete current_scene_;
    }
    if (asset_store_)
    {
        asset_store_->Clean();
        delete asset_store_;
    }
    if (renderer_)
    {
        SDL_DestroyRenderer(renderer_);
    }
    if (window_)
    {
        SDL_DestroyWindow(window_);
    }
    TTF_Quit();
    Mix_CloseAudio();
    Mix_Quit();
    SDL_Quit();
}

void Game::DrawGrid(const glm::vec2& top_left, const glm::vec2& bottom_right, float grid_width, SDL_FColor fcolor)
{
    SDL_SetRenderDrawColorFloat(renderer_, fcolor.r, fcolor.g, fcolor.b, fcolor.a);
    for (float x = top_left.x; x <= bottom_right.x; x += grid_width)
    {
        if (x < 0.f || x > screen_size_.x)
        {
            continue;
        }
        SDL_RenderLine(renderer_, x, top_left.y, x, bottom_right.y);
    }
    for (float y = top_left.y; y <= bottom_right.y; y += grid_width)
    {
        if (y < 0.f || y > screen_size_.y)
        {
            continue;
        }
        SDL_RenderLine(renderer_, top_left.x, y, bottom_right.x, y);
    }
    SDL_SetRenderDrawColorFloat(renderer_, 0, 0, 0, 1);
}

void Game::DrawBoundary(const glm::vec2& top_left, const glm::vec2& bottom_right, float boundary_width,
                        SDL_FColor fcolor)
{
    SDL_SetRenderDrawColorFloat(renderer_, fcolor.r, fcolor.g, fcolor.b, fcolor.a);
    for (float i = 0.f; i < boundary_width; i++)
    {
        auto rect = SDL_FRect{.x = top_left.x - i,
                              .y = top_left.y - i,
                              .w = bottom_right.x - top_left.x + 2 * i,
                              .h = bottom_right.y - top_left.y + 2 * i};
        SDL_RenderRect(renderer_, &rect);
    }
    SDL_SetRenderDrawColorFloat(renderer_, 0, 0, 0, 1);
}

void Game::RenderTexture(const Texture& texture, const glm::vec2& position, const glm::vec2& size)
{
    SDL_FRect dst_rect = {position.x, position.y, size.x, size.y};
    SDL_RenderTextureRotated(renderer_, texture.texture, &texture.src_rect, &dst_rect, texture.angle, nullptr,
                             texture.flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

void Game::RenderFillCircle(const glm::vec2& position, const glm::vec2& size, float alpha)
{
    auto texture = asset_store_->texture("assets/UI/circle.png");
    SDL_FRect dst_rect = {position.x, position.y, size.x, size.y};
    SDL_SetTextureAlphaModFloat(texture, alpha);
    SDL_RenderTexture(renderer_, texture, nullptr, &dst_rect);
}