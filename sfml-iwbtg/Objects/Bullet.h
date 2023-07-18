#pragma once
#include "SpriteGo.h"
#include "ObjectPool.h"
#include "TileMap.h"

class Bullet : public SpriteGo
{
protected:
	sf::Vector2f direction;
	float speed = 0.f;
	float range = 0.f;
	int damage = 0;

	TileMap* tileMap;
public:
	ObjectPool<Bullet>* pool;
	
	Bullet(const std::string id = "", const std::string n = "");
	virtual ~Bullet() override;

	void SetTileMap(TileMap* tileMap);
	void Fire(const sf::Vector2f& pos, const sf::Vector2f& dir, float speed);

	virtual void Init()override;
	virtual void Reset()override;
	virtual void Release() override;

	virtual void Update(float dt)override;
	virtual void Draw(sf::RenderWindow& window)override;

	Tile::Types CollideCheck();
};

