#pragma once

#include "Sprite.h"

class SpriteAnim : public Sprite
{
public:
    void Update(float delta_time) override;

    static SpriteAnim* AddSpriteAnimChild(ObjectScreen* parent, const std::string& path, float scale, Anchar anchor);

    void set_texture(const Texture& t) override;

    int current_frame() const
    {
        return current_frame_;
    }
    void set_current_frame(int f)
    {
        current_frame_ = f;
    }
    int total_frame() const
    {
        return total_frame_;
    }
    void set_total_frame(int f)
    {
        total_frame_ = f;
    }
    int fps() const
    {
        return fps_;
    }
    void set_fps(int f)
    {
        fps_ = f;
    }
    float frame_timer() const
    {
        return frame_timer_;
    }
    void set_frame_timer(float t)
    {
        frame_timer_ = t;
    }
    bool is_loop() const
    {
        return is_loop_;
    }
    void set_loop(bool l)
    {
        is_loop_ = l;
    }

private:
    int current_frame_{};
    int total_frame_{};
    int fps_{10};
    float frame_timer_{};
    bool is_loop_{true};
};