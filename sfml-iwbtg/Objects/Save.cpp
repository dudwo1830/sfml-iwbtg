#include "stdafx.h"
#include "Save.h"

Save::Save(const std::string& textureId, const std::string& name)
    :SpriteGo(textureId, name)
{
}

Save::~Save()
{
}

const sf::Vector2f& Save::GetRestartPos()
{
    return restartPos;
}

void Save::Init()
{
    SpriteGo::Init();
}

void Save::Release()
{
    SpriteGo::Release();
}

void Save::Reset()
{
    SpriteGo::Reset();
}

void Save::Update(float deltaTime)
{
    SpriteGo::Update(deltaTime);
}

void Save::Draw(sf::RenderWindow& window)
{
    SpriteGo::Draw(window);
}
