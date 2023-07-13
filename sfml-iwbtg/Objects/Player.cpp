#include "stdafx.h"
#include "Player.h"
#include "InputMgr.h"
#include "ResourceMgr.h"
Player::Player(const std::string& textureId, const std::string& name)
	:SpriteGo(textureId, name)
{
}

Player::~Player()
{
	Release();
}

void Player::Init()
{
	SpriteGo::Init();
	direction = { 0.f, 0.f };
	velocity = 0.f;
	gravityAccel = 9.8f;
	gravity = 50.f;
	speed = 500.f;
	jumpForce = 400.f;

	isGround = false;
	isJumping = false;
	jumpCount = 2;

	SetOrigin(Origins::MC);
}

void Player::Release()
{
	SpriteGo::Release();
}

void Player::Reset()
{
	SpriteGo::Reset();
	sprite.setTexture(*RESOURCE_MGR.GetTexture("graphics/Player/PlayerMask.png"));

	SetPosition({0.f, 0.f});
	SetOrigin(origin);
}

void Player::Update(float deltaTime)
{
	SpriteGo::Update(deltaTime);
	velocity += gravity * gravityAccel * deltaTime;

	//ÀÌµ¿
	float horizonRaw = INPUT_MGR.GetAxisRaw(Axis::Horizontal);
	if (isGround)
	{
		velocity = 0.f;
	}
	position.x += horizonRaw * speed * deltaTime;
	position.y += velocity * deltaTime;

	SetPosition(position);
	isGround = false;
}

bool Player::GetGround() const
{
	return isGround;
}

void Player::SetGround(bool isGround)
{
	this->isGround = isGround;
}

bool Player::GetJumping() const
{
	return isJumping;
}

void Player::SetJumping(bool isJumping)
{
	this->isJumping = isJumping;
}

int Player::GetJumpCount() const
{
	return jumpCount;
}

void Player::SetJumpCount(int count)
{
	this->jumpCount = count;
}

bool Player::GetFlipX() const
{
	return false;
}

void Player::SetFlipX(bool flip)
{
	flipX = flip;
	sf::Vector2f scale = sprite.getScale();
	scale.x = (!flipX) ? abs(scale.x) : -abs(scale.x);
	sprite.setScale(scale);
}