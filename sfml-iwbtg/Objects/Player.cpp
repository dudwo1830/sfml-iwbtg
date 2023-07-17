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
	speed = 300.f;

	isGround = false;
	jump = false;
	djump = false;

	SetPosition({0.f, 0.f});
	SetOrigin(origin);
}

void Player::Update(float deltaTime)
{
	SpriteGo::Update(deltaTime);
	Collision collision = CollideCheck();

	MovePlayer(deltaTime, collision);
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

void Player::MovePlayer(float deltaTime, Player::Collision collision)
{
	velocity += gravity * gravityAccel * deltaTime;
	horizonRaw = INPUT_MGR.GetAxisRaw(Axis::Horizontal);
	switch (collision)
	{
	case Player::Collision::Top:
		break;
	case Player::Collision::Bottom:
		velocity = 0.f;
		jump = false;
		djump = false;
		break;
	case Player::Collision::Left:
		std::cout << "Left" << std::endl;
		horizonRaw = 0.f;
		break;
	case Player::Collision::Right:
		std::cout << "Right" << std::endl;
		horizonRaw = 0.f;
		break;
	}

	//이동
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Z))
	{
		std::cout << "jump!" << std::endl;
		velocity = -jumpForce;
		jump = true;
	}

	position.x += horizonRaw * speed * deltaTime;
	position.y += velocity * deltaTime;

	SetPosition(position);
}

Player::Collision Player::CollideCheck()
{
	float tileSizeX = tileMap->GetTileSize().x;
	sf::Vector2i playerTile = (sf::Vector2i)(position / tileSizeX);

	std::vector<sf::Vector2i> nearTiles;
	nearTiles.push_back({ playerTile.x, playerTile.y - 1 });
	nearTiles.push_back({ playerTile.x, playerTile.y + 1 });
	nearTiles.push_back({ playerTile.x - 1, playerTile.y });
	nearTiles.push_back({ playerTile.x + 1, playerTile.y });
	
	//타일 개수
	sf::Vector2i tileMatrix = tileMap->GetTileMatrix();
	
	for (int i = 0; i < nearTiles.size(); i++)
	{
		int tileIndex = tileMap->GetTileIndex(nearTiles[i]);
		//잘못된 index
		if (tileIndex < 0 || tileIndex >= tileMatrix.x * tileMatrix.y)
			continue;

		Tile& tile = tileMap->tiles[tileIndex];
		//None
		if (tile.type == Tile::Types::None)
			continue;

		if (tile.y < playerTile.y)
		{
			//Top
			return Collision::Top;
		}
		else if (tile.y == playerTile.y)
		{
			std::cout << "bottom" << std::endl;
			if (INPUT_MGR.GetKeyDown(sf::Keyboard::Return))
			{
				std::cout << tile.position.y  << ", " << position.y << std::endl;
			}
			position.y = tile.position.y;
			//Bottom
			return Collision::Bottom;
		}
		else if (tile.x < playerTile.x)
		{
			//Left
			return Collision::Left;
		}
		else if (tile.x > playerTile.x)
		{
			//Right
			return Collision::Right;
		}
	}
	return Collision::None;
}