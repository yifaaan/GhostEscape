#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <string>
#include <unordered_map>

class AssetStore {
   public:
    explicit AssetStore(SDL_Renderer* renderer) : renderer_(renderer) {}
    ~AssetStore() = default;

    void LoadTextures(std::string path);
    void LoadChunks(std::string path);
    void LoadMusics(std::string path);
    void LoadFonts(std::string path, int font_size);

    void Clean();

    SDL_Texture* texture(std::string path);
    Mix_Chunk* chunk(std::string path);
    Mix_Music* music(std::string path);
    TTF_Font* font(std::string path, int font_size);

    const std::unordered_map<std::string, SDL_Texture*>& textures() const { return textures_; }
    const std::unordered_map<std::string, Mix_Chunk*> chunks() const { return chunks_; }
    const std::unordered_map<std::string, Mix_Music*> musics() const { return musics_; }
    const std::unordered_map<std::string, TTF_Font*> fonts() const { return fonts_; }

   private:
    SDL_Renderer* renderer_{};
    std::unordered_map<std::string, SDL_Texture*> textures_;
    std::unordered_map<std::string, Mix_Chunk*> chunks_;
    std::unordered_map<std::string, Mix_Music*> musics_;
    std::unordered_map<std::string, TTF_Font*> fonts_;
};