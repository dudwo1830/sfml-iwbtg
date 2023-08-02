#pragma once
#include "SpriteGo.h"
#include "ObjectPool.h"
#include "AnimationController.h"

class TileMap;
class Bullet;
class Collider;

class Player : public SpriteGo
{
protected:
	AnimationController animation;
	sf::Vector2f hitBoxSize = { 11.f, 21.f };
	sf::RectangleShape hitBox;
	sf::FloatRect playerBounds;

	//이동
	sf::Vector2f prevPos;
	sf::Vector2f velocity;
	float gravityAccel = 450.f;
	float gravity = 50.f;
	float speed = 120.f;
	bool flipX = false;

	//점프
	bool jump = false;
	float jumpForce = 260.f;
	float minJumpForce = 200.f;
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

	//생사
	bool isAlive = true;

	//주변타일 시각화
	std::vector<sf::RectangleShape> newTileBounds;
	
	//test
	bool testMode = false;
	Collider* collider = nullptr;

	Player(const Player& other) = delete;
	bool operator==(const Player& other) const = delete;
public:
	//총알
	ObjectPool<Bullet> poolBullets;
	float bulletSpeed = 500.f;

	Player(const std::string& textureId = "", const std::string& name = "");
	virtual ~Player() override;

	//hitBox
	const sf::FloatRect& GetHitBoxBounds() { return hitBox.getGlobalBounds(); };
	const sf::RectangleShape& GetHitBox() { return hitBox; }

	virtual void SetPosition(const sf::Vector2f& position) override;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Update(float deltaTime) override;
	virtual void Draw(sf::RenderWindow& window) override;

	bool GetFlipX() { return flipX; }
	bool GetAlive() const { return isAlive; }
	const sf::Vector2f& GetPrevPos() { return prevPos; }

	void SetFlipX(bool flip);
	void SetDJump(bool djump) { this->djump = djump; }
	void SetWallClimb(bool wallClimb);
	void SetTileMap(TileMap* map) { this->tileMap = map; }

	void UpdateAnimation();
	void Jump();
	void Shoot();
	void Die();
	
	void CollideWindow();
	void CollideCheck();
	void ResetCollision();

	void SetCollider(Collider* collider) { this->collider = collider; }
	Collider* GetCollider() { return collider; }
};

