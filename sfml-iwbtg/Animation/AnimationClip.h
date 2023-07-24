#pragma once

enum class AnimationLoopTypes
{
    Single,
    Loop,
};

struct AnimationFrame
{
    std::string textureId;
    sf::IntRect texCoord;
    //std::function<void()> action = nullptr;
};

struct AnimationClip
{
    std::string id;
    std::vector<AnimationFrame> frames;
    AnimationLoopTypes loopType;
    int fps;

    bool LoadFromFile(const std::string path);
    AnimationClip() = default;
    AnimationClip(const AnimationClip& other) = delete;
};
