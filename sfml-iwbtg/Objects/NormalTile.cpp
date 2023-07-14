#include "stdafx.h"
#include "NormalTile.h"

NormalTile::NormalTile(const std::string& textureId, const std::string& name)
    :Tile(textureId, name)
{
}

NormalTile::~NormalTile()
{
    Release();
}

void NormalTile::Reset()
{
    Tile::Reset();
}

void NormalTile::Init()
{
    textureId = "graphics/Blocks/Block001.png";
    SetType(Types::Normal);

    vertexArray.setPrimitiveType(sf::Quads);
    vertexArray.resize(4);

    sf::Vector2f texSize = { 32.f, 32.f };
    sf::Vector2f texOffsets[4] =
    {
        { 0.f, 0.f },
        { texSize.x, 0.f },
        { texSize.x, texSize.y },
        { 0.f, texSize.y }
    };
    for (int k = 0; k < 4; ++k)
    {
        int vertexIndex = k;
        vertexArray[vertexIndex].texCoords = texOffsets[k];
        vertexArray[vertexIndex].texCoords.y += texSize.y;
        std::cout << vertexArray[vertexIndex].texCoords.x << std::endl;
        std::cout << vertexArray[vertexIndex].texCoords.y << std::endl;
    }

    CollideTop = []() {
        std::cout << "CollideTop" << std::endl;
    };
    CollideLeft = []() {
        std::cout << "CollideLeft" << std::endl;
    };    
    CollideRight = []() {
        std::cout << "CollideRight" << std::endl;
    };    
    CollideBottom = []() {
        std::cout << "CollideBottom" << std::endl;
    };
}

void NormalTile::Draw(sf::RenderWindow& window)
{
    Tile::Draw(window);
}
