#pragma once
#include "SpriteGo.h"
#include "ObjectPool.h"
#include "AnimationController.h"

class TileMap;
class Bullet;

class Player : public SpriteGo
{
public:
	enum class Collision
	{
		None = -1,
		Top,
		Bottom,
		Left,
		Right,
	};
protected:
	sf::Vector2f direction;
	sf::Vector2f prevPos;

	float velocity = 0.f;
	float gravityAccel = 9.8f;
	float gravity = 100.f;
	float speed = 500.f;
	float horizonRaw = 0.f; 

	bool isGround = false;
	bool jump = false;
	float jumpForce = 300.f;
	bool djump = false;
	float djumpForce = 200.f;

	bool flipX = false;

	TileMap* tileMap = nullptr;
	ObjectPool<Bullet> poolBullets;

	Player(const Player& other) = delete;
	bool operator==(const Player& other) const = delete;
public:
	Player(const std::string& textureId = "", const std::string& name = "");
	virtual ~Player();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Update(float deltaTime) override;

	bool GetGround() const;
	void SetGround(bool isGround);
	bool GetFlipX() const;
	void SetFlipX(bool flip);
	void SetTileMap(TileMap* map);
	
	void MovePlayer(float deltaTime, Player::Collision collision);
	Collision CollideCheck();
	void Jump(float deltaTime);
};

