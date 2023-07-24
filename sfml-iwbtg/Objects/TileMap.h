#pragma once
#include "VertexArrayGo.h"
struct Tile
{
	enum class Type
	{
		None = 0,
		Grass,
		Ground,
		LongGround,
		Killer,
	};
	int x = 0;
	int y = 0;
	Type type = Type::None;

	sf::Vector2f position;
};

class TileMap : public VertexArrayGo
{
protected:
	sf::Vector2i tileMatrix;
	sf::Vector2f tileSize;
	sf::Vector2f textureSize;
	
public:
	TileMap(const std::string& textureId = "", const std::string& n = "");
	virtual ~TileMap() override;

	bool Load(const std::string& filePath);

	std::vector<Tile> tiles;
	
	const sf::Vector2i& GetTileMatrix();
	const sf::Vector2f& GetTileSize();
	const sf::Vector2f& GetTextureSize();
	const int GetTileIndex(const sf::Vector2i& coord) const;

	void VertexRotateQuad(sf::Vertex* quad, int rotate);
};