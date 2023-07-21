#pragma once
#include "GameObject.h"
#include "SpriteGo.h"

//struct Obstacle
//{
//	enum class Type
//	{
//		None,
//		Item,
//		Save,
//		WallClimb,
//		Trap,
//	};
//	SpriteGo* spriteGo;
//};

class ObstaclesMap : public GameObject
{
protected:
	sf::Vector2f tileSize = { 32.f, 32.f };
	
public:
	ObstaclesMap(const std::string& name = "");
	virtual ~ObstaclesMap() override;

	void SetTileSize(sf::Vector2f& tileSize) { this->tileSize = tileSize; }
	bool Load(const std::string& filePath);

	virtual void Init()override;
	virtual void Reset()override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
};

