#include "stdafx.h"
#include "Player.h"
#include "TileMap.h"
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

	SetOrigin(Origins::BC);
}

void Player::Release()
{
	SpriteGo::Release();
}

void Player::Reset()
{
	SpriteGo::Reset();
	sprite.setTexture(*RESOURCE_MGR.GetTexture("graphics/Player/PlayerMask.png"));

	direction = { 0.f, 0.f };
	velocity = 0.f;
	gravityAccel = 9.8f;
	gravity = 50.f;
	speed = 500.f;

	isGround = false;
	jump = false;
	djump = false;

	SetPosition({0.f, 0.f});
	SetOrigin(origin);
}

void Player::Update(float deltaTime)
{
	SpriteGo::Update(deltaTime);
	velocity += gravity * gravityAccel * deltaTime;

	CollideCheck();

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Z))
	{
		if (isGround && !djump)
		{
			velocity = -minJumpForce;
			isGround = false;
		}
	}

	//ÀÌµ¿
	float horizonRaw = INPUT_MGR.GetAxisRaw(Axis::Horizontal);
	if (isGround)
	{
		velocity = 0.f;
		jump = false;
		djump = false;
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

void Player::SetTileMap(TileMap* map)
{
	this->tileMap = map;
}

void Player::CollideCheck()
{
	float tileSizeX = tileMap->GetTileSize().x;
	sf::Vector2i playerTileIndex = (sf::Vector2i)(GetPosition() / tileSizeX);

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Return))
	{
		std::cout << playerTileIndex.x << ", " << playerTileIndex.y << std::endl;
	}

	int tileSize = tileMap->tiles.size();
	for (int i = 0; i < tileSize; i++)
	{
		if (tileMap->tiles[i].type == Tile::Types::None)
		{
			continue;
		}

		if (tileMap->tiles[i].x == playerTileIndex.x && tileMap->tiles[i].y == playerTileIndex.y)
		{
			isGround = true;
			break;
		}
	}
}

void Player::Jump(float deltaTime) {
	isGround = false;
	jump = true;

	float jumpTime = 0.f;
	while (INPUT_MGR.GetKey(sf::Keyboard::Z) && jumpTime < 1.f) {
		velocity = -minJumpForce * jumpTime * deltaTime;
		jumpTime += deltaTime;
	}
}