#pragma once
#include "SpriteGo.h"
#include "ObjectPool.h"
#include "AnimationController.h"

class TileMap;
class Bullet;

class Player : public SpriteGo
{
protected:
	sf::Vector2f direction;
	sf::Vector2f prevPos;
	
	//이동
	float velocity = 0.f;
	float gravityAccel = 9.8f;
	float gravity = 100.f;
	float speed = 500.f;
	float horizonRaw = 0.f; 
	bool flipX = false;

	//점프
	bool jump = false;
	float jumpForce = 300.f;
	bool djump = false;
	float djumpForce = 200.f;
	bool wallClimb = false;
	float wallClimbGravity = 50.f;

	//충돌
	TileMap* tileMap = nullptr;
	bool topCollision = false;
	bool bottomCollision = false;
	bool leftCollision = false;
	bool rightCollision = false;

	//사망
	bool isAlive = true;

	ObjectPool<Bullet> poolBullets;

	//판정?
	std::vector<sf::RectangleShape> newTileBounds;

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
	
	void CollideCheck();
	void ResetCollision();


	//test
	void MoveTest(float deltaTime);
};

