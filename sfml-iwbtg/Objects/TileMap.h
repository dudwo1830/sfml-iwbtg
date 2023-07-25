#pragma once
#include "VertexArrayGo.h"
class Spike;

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
	std::list<Spike*>* spikeList;

public:
	TileMap(const std::string& textureId = "", const std::string& n = "");
	virtual ~TileMap() override;

	bool Load(const std::string& filePath);

	std::vector<Tile> tiles;
	
	const sf::Vector2i& GetTileMatrix();
	const sf::Vector2f& GetTileSize();
	const sf::Vector2f& GetTextureSize();
	const int GetTileIndex(const sf::Vector2i& coord) const;
	void SetSpikeList(std::list<Spike*>* list) { this->spikeList = list; };
	void AddSpike(float angle, const sf::Vector2f& point);

	void VertexRotateQuad(sf::Vertex* quad, float angle);
};