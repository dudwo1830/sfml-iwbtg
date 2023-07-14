#pragma once
#include "SpriteGo.h"
#include "AnimationController.h"

class TileMap;

class Player : public SpriteGo
{
protected:

	sf::Vector2f direction = { 0.f, 0.f };
	float velocity = 0.f;
	float gravityAccel = 9.8f;
	float gravity = 100.f;
	float speed = 500.f;
	float djumpForce = 200.f;
	float minJumpForce = 100.f;
	float maxJumpForce = 400.f;

	bool isGround = false;
	bool jump = false;
	bool djump = false;

	bool flipX = false;

	TileMap* tileMap = nullptr;

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
	bool GetJumping() const;
	void SetJumping(bool isJumping);
	bool GetFlipX() const;
	void SetFlipX(bool flip);
	void SetTileMap(TileMap* map);

	void CollideCheck();
};

