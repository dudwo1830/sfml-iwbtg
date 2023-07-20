#pragma once
#include "SpriteGo.h"
#include "ObjectPool.h"
#include "AnimationController.h"

class TileMap;
class Bullet;

class Player : public SpriteGo
{
protected:
	//이동
	sf::Vector2f velocity;
	float gravityAccel = 9.8f;
	float gravity = 50.f;
	float speed = 300.f;
	bool flipX = false;

	//점프
	bool jump = false;
	float jumpForce = 600.f;
	bool jumping = false;
	bool djump = false;
	float djumpForce = 300.f;
	bool wallClimb = false;
	float wallClimbGravity = 50.f;

	//충돌
	TileMap* tileMap = nullptr;
	bool topCollision = false;
	bool bottomCollision = false;
	bool leftCollision = false;
	bool rightCollision = false;

	//생사
	bool isAlive = true;

	//총알
	ObjectPool<Bullet> poolBullets;

	//주변타일 시각화
	std::vector<sf::RectangleShape> newTileBounds;
	
	//test
	bool testMode = false;

	Player(const Player& other) = delete;
	bool operator==(const Player& other) const = delete;
public:
	Player(const std::string& textureId = "", const std::string& name = "");
	virtual ~Player();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Update(float deltaTime) override;
	virtual void Draw(sf::RenderWindow& window) override;

	bool GetFlipX() const;
	void SetFlipX(bool flip);
	void SetTileMap(TileMap* map);
	bool GetAlive() const;
	
	void MovePlayer(float deltaTime);
	void Jump(float deltaTime);
	void Shoot();
	void Die();
	
	void CollideWindowCheck();
	void CollideCheck();
	void ResetCollision();


	//test
	void MoveTest(float deltaTime);
};

