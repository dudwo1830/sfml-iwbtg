#include "stdafx.h"
#include "Tile.h"
#include "Player.h"

Tile::Tile(const std::string& textureId, const std::string& name)
    :SpriteGo(textureId, name)
{
}

Tile::~Tile()
{
    Release();
}

void Tile::Init()
{
    SpriteGo::Init();
}

void Tile::Release()
{
    SpriteGo::Release();
}

void Tile::Reset()
{
    SpriteGo::Reset();
}

void Tile::Update(float deltaTime)
{
    SpriteGo::Update(deltaTime);
    if (player == nullptr)
    {
        return;
    }

    bool isCollide = sprite.getGlobalBounds().intersects(player->GetSprite().getGlobalBounds());
    if (isCollide && CollideTop != nullptr)
    {
        CollideTop();
    }
}

Player* Tile::GetPlayer()
{
    return player;
}

void Tile::SetPlayer(Player* player)
{
    this->player = player;
}

void Tile::SetType(Types type)
{
    this->type = type;
}
