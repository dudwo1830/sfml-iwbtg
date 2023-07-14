#include "stdafx.h"
#include "TileMap.h"
#include "rapidcsv.h"

TileMap::TileMap(const std::string& textureId, const std::string& n)
    : VertexArrayGo(textureId, n)
{
}

TileMap::~TileMap()
{
}

bool TileMap::Load(const std::string& filePath)
{
    rapidcsv::Document map(filePath, rapidcsv::LabelParams(-1, -1));
    tileMatrix = { (int)map.GetColumnCount(), (int)map.GetRowCount() };

    for (int i = 0; i < tileMatrix.y; ++i)
    {
        for (int j = 0; j < tileMatrix.x; ++j)
        {
            Tile tile;
            tile.x = j;
            tile.y = i;
            tile.type = (Tile::Types)map.GetCell<int>(j, i);
            tiles.push_back(tile);
        }
    }

    tileSize = { 32.f, 32.f };
    textureSize = { 32.f, 32.f };
    sf::Vector2f texOffsets[4] =
    {
        { 0.f, 0.f },
        { textureSize.x, 0.f },
        { textureSize.x, textureSize.y },
        { 0.f, textureSize.y }
    };


    // resize the vertex array to fit the level size
    vertexArray.setPrimitiveType(sf::Quads);
    vertexArray.resize(tileMatrix.x * tileMatrix.y * 4);
    sf::Vector2f startPos = { 0, 0 };
    sf::Vector2f currPos = startPos;

    sf::Vector2f offsets[4] =
    {
        { 0.f, 0.f },
        { tileSize.x, 0.f },
        { tileSize.x, tileSize.y },
        { 0.f, tileSize.y }
    };

    for (int i = 0; i < tileMatrix.y; ++i)
    {
        for (int j = 0; j < tileMatrix.x; ++j)
        {
            int tileIndex = tileMatrix.x * i + j;
            int texIndex = (int)tiles[tileIndex].type;
            if (texIndex == 0)
            {
                currPos.x += tileSize.x;
                continue;
            }
            for (int k = 0; k < 4; ++k)
            {
                int vertexIndex = tileIndex * 4 + k;
                vertexArray[vertexIndex].position = currPos + offsets[k];
                vertexArray[vertexIndex].texCoords = texOffsets[k];
                vertexArray[vertexIndex].texCoords.y += textureSize.y * (texIndex - 1);
            }
            currPos.x += tileSize.x;
        }
        currPos.x = startPos.x;
        currPos.y += tileSize.y;
    }

    return true;
}

const sf::Vector2i& TileMap::GetTileMatrix()
{
    return tileMatrix;
}

const sf::Vector2f& TileMap::GetTileSize()
{
    return tileSize;
}
const sf::Vector2f& TileMap::GetTextureSize()
{
    return textureSize;
}