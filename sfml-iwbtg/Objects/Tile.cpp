#include "stdafx.h"
#include "Tile.h"
#include "Player.h"

Tile::Tile(const std::string& textureId, const std::string& name)
    :VertexArrayGo(textureId, name)
{
}

Tile::~Tile()
{
    Release();
}

void Tile::Init()
{
    VertexArrayGo::Init();
}

void Tile::Release()
{
    VertexArrayGo::Release();
}

void Tile::Reset()
{
    VertexArrayGo::Reset();
    sf::Vector2u textureSize = GetTextureSize();
}

void Tile::Update(float deltaTime)
{
    VertexArrayGo::Update(deltaTime);
    if (player == nullptr)
    {
        return;
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