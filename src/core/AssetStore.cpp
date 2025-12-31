#include "AssetStore.h"

#include <algorithm>
#include <format>
#include <ranges>

void AssetStore::LoadTextures(std::string path)
{
    auto texture = IMG_LoadTexture(renderer_, path.c_str());
    if (!texture)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "IMG_LoadTexture Error: %s", SDL_GetError());
        return;
    }
    textures_.emplace(std::move(path), texture);
}

void AssetStore::LoadChunks(std::string path)
{
    auto chunk = Mix_LoadWAV(path.c_str());
    if (!chunk)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Mix_LoadWAV Error: %s", SDL_GetError());
    }
    chunks_.emplace(std::move(path), chunk);
}

void AssetStore::LoadMusics(std::string path)
{
    auto music = Mix_LoadMUS(path.c_str());
    if (!music)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Mix_LoadMUS Error: %s", SDL_GetError());
    }
    musics_.emplace(std::move(path), music);
}

void AssetStore::LoadFonts(std::string path, int font_size)
{
    auto font = TTF_OpenFont(path.c_str(), font_size);
    if (!font)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "LoadFonts Error: %s", SDL_GetError());
    }
    fonts_.emplace(std::format("{}-{}", path, font_size), font);
}

void AssetStore::Clean()
{
    std::ranges::for_each(textures_, [](auto& p) { SDL_DestroyTexture(p.second); });
    textures_.clear();
    std::ranges::for_each(chunks_, [](auto& p) { Mix_FreeChunk(p.second); });
    chunks_.clear();
    std::ranges::for_each(musics_, [](auto& p) { Mix_FreeMusic(p.second); });
    musics_.clear();
    std::ranges::for_each(fonts_, [](auto& p) { TTF_CloseFont(p.second); });
    fonts_.clear();
}

SDL_Texture* AssetStore::texture(std::string path)
{
    auto it = textures_.find(path);
    if (it == textures_.end())
    {
        LoadTextures(path);
        it = textures_.find(path);
    }
    if (it == textures_.end())
    {
        return nullptr;
    }
    return it->second;
}

Mix_Chunk* AssetStore::chunk(std::string path)
{
    auto it = chunks_.find(path);
    if (it == chunks_.end())
    {
        LoadChunks(path);
        it = chunks_.find(path);
    }
    if (it == chunks_.end())
    {
        return nullptr;
    }
    return it->second;
}

Mix_Music* AssetStore::music(std::string path)
{
    auto it = musics_.find(path);
    if (it == musics_.end())
    {
        LoadMusics(path);
        it = musics_.find(path);
    }
    if (it == musics_.end())
    {
        return nullptr;
    }
    return it->second;
}

TTF_Font* AssetStore::font(std::string path, int font_size)
{
    auto it = fonts_.find(std::format("{}-{}", path, font_size));
    if (it == fonts_.end())
    {
        LoadFonts(path, font_size);
        it = fonts_.find(std::format("{}-{}", path, font_size));
    }
    if (it == fonts_.end())
    {
        return nullptr;
    }
    return it->second;
}