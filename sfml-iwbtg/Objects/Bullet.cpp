#include "stdafx.h"
#include "Bullet.h"
#include "Scene.h"
#include "SceneMgr.h"
#include "ResourceMgr.h"

Bullet::Bullet(const std::string id, const std::string n)
	:SpriteGo(id, n)
{
}

Bullet::~Bullet()
{
}

void Bullet::SetTileMap(TileMap* tileMap)
{
	this->tileMap = tileMap;
}

void Bullet::Fire(const sf::Vector2f& pos, const sf::Vector2f& dir, float speed)
{
	SetPosition(pos);
	direction = dir;
	this->speed = speed;
}

void Bullet::Init()
{
	SpriteGo::Init();
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Player/Bullet.csv"));
	animation.SetTarget(&sprite);
	SetOrigin(Origins::MC);
}

void Bullet::Reset()
{
	//SpriteGo::Reset();
	animation.Play("Bullet");
	sprite.setRotation(0.f);
	SetPosition(0.f, 0.f);
	direction = { 0.f, 0.f };
	damage = 0;
	range = 2000.f;
}

void Bullet::Release()
{
	//SpriteGo::Release();
}

void Bullet::Update(float dt)
{
	animation.Update(dt);
	//SpriteGo::Update(dt);
	range -= speed * dt;
	if (range <= 0.f)
	{
		SCENE_MGR.GetCurrentScene()->RemoveGo(this);
		pool->Return(this);
		return;
	}

	position += direction * speed * dt;
	sprite.setPosition(position);

	
	if (tileMap != nullptr)
	{
		if (CollideTileCheck() != Tile::Type::None)
		{
			SCENE_MGR.GetCurrentScene()->RemoveGo(this);
			pool->Return(this);
		}
	}
}

void Bullet::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

Tile::Type Bullet::CollideTileCheck()
{
	sf::Vector2f tileSize = tileMap->GetTileSize();
	sf::Vector2i bulletTile = (sf::Vector2i)(position / tileSize.x);
	sf::Vector2i tileMatrix = tileMap->GetTileMatrix();
	std::vector<sf::Vector2i> nearTiles;

	int tileIndexSide = (direction.x < 0.f) ? 0 : 1;
	nearTiles.push_back({ bulletTile.x + tileIndexSide, bulletTile.y });

	for (int i = 0; i < nearTiles.size(); i++)
	{
		int tileIndex = tileMap->GetTileIndex(nearTiles[i]);
		if (tileIndex < 0 || tileIndex >= tileMatrix.x * tileMatrix.y)
			continue;

		Tile& tile = tileMap->tiles[tileIndex];
		if (tile.type == Tile::Type::None)
			continue;

		sf::FloatRect tileBounds(tile.position.x, tile.position.y, tileSize.x, tileSize.y);

		if (sprite.getGlobalBounds().intersects(tileBounds))
		{
			return tile.type;
		}
	}

	return Tile::Type::None;
}