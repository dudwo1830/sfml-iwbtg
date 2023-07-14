#pragma once
#include "Tile.h"
class NormalTile : public Tile
{
protected:

	NormalTile(const NormalTile& other) = delete;
	bool operator==(const NormalTile& other) const = delete;
public:
	NormalTile(const std::string& textureId = "", const std::string& name = "");
	virtual ~NormalTile();

	virtual void Reset() override;
	virtual void Init() override;
	void Draw(sf::RenderWindow& window) override;
};

