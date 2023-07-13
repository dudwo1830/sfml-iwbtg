#pragma once
#include "SpriteGo.h"
#include "AnimationController.h"

class Player : public SpriteGo
{
protected:

	sf::Vector2f direction = { 0.f, 0.f };
	float velocity = 0.f;
	float gravityAccel = 9.8f;
	float gravity = 100.f;
	float speed = 500.f;
	float jumpForce = 400.f;

	bool isGround = true;
	bool isJumping = false;
	int jumpCount = 2;

	Player(const Player& other) = delete;
	bool operator==(const Player& other) const = delete;
public:
	Player(const std::string& textureId = "", const std::string& name = "");
	virtual ~Player();

	bool GetGround();
	void SetGround(bool isGround);
	bool GetJumping();
	void SetJumping(bool isJumping);
	int GetJumpCount();
	void SetJumpCount(int count);

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float deltaTime) override;
};

