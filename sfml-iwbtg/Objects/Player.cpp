#include "stdafx.h"
#include "Player.h"
#include "ResourceMgr.h"
Player::Player(const std::string& textureId, const std::string& name)
	:SpriteGo(textureId, name)
{
}

Player::~Player()
{
}

bool Player::GetGround()
{
    return isGround;
}

void Player::SetGround(bool isGround)
{
	this->isGround = isGround;
}

bool Player::GetJumping()
{
    return isJumping;
}

void Player::SetJumping(bool isJumping)
{
	this->isJumping = isJumping;
}

int Player::GetJumpCount()
{
    return jumpCount;
}

void Player::SetJumpCount(int count)
{
	this->jumpCount = count;
}

void Player::Init()
{
	SpriteGo::Init();
	direction = { 0.f, 0.f };
	velocity = 0.f;
	gravityAccel = 9.8f;
	gravity = 100.f;
	speed = 500.f;
	jumpForce = 400.f;

	isGround = true;
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
	velocity = gravity * gravityAccel * deltaTime;
	
}