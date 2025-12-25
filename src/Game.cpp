#include "Game.h"

void Game::Run()
{
    while (is_running_)
    {
        auto start = SDL_GetTicksNS();
        HandleEvents();
        Update(0);
        Render();
        auto end = SDL_GetTicksNS();
        auto elapsed = end - start;
        if (elapsed < frame_delay_) 
        {
            SDL_DelayNS(frame_delay_ - elapsed);
            delta_time_ = frame_delay_/ 1.0e9;
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
}

void Game::HandleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_EVENT_QUIT:
            is_running_ = false;
            break;
        default:
            break;
        }
    }
}

void Game::Update(float delta_time)
{

}

void Game::Render()
{

}

void Game::Clean()
{
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
    SDL_Quit();
}