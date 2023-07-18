#include "stdafx.h"
#include "Player.h"
#include "TileMap.h"
#include "InputMgr.h"
#include "ResourceMgr.h"
#include "Bullet.h"
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

	//test
	{
		sf::RectangleShape shape;
		shape.setSize({ 11.f, 2.f });
		Utils::SetOrigin(shape, Origins::MC);
		shape.setFillColor(sf::Color::Green);
		rectArr.push_back(shape);
	}
	{
		sf::RectangleShape shape;
		shape.setSize({ 11.f, 2.f });
		Utils::SetOrigin(shape, Origins::MC);
		shape.setFillColor(sf::Color::White);
		rectArr.push_back(shape);
	}
	{
		sf::RectangleShape shape;
		shape.setSize({ 2.f, 21.f });
		Utils::SetOrigin(shape, Origins::MC);
		shape.setFillColor(sf::Color::Blue);
		rectArr.push_back(shape);
	}
	{
		sf::RectangleShape shape;
		shape.setSize({ 2.f, 21.f });
		Utils::SetOrigin(shape, Origins::MC);
		shape.setFillColor(sf::Color::Yellow);
		rectArr.push_back(shape);
	}

	SetOrigin(Origins::BC);
}

void Player::Release()
{
	SpriteGo::Release();
}

void Player::Reset()
{
	SpriteGo::Reset();
	sprite.setTexture(*RESOURCE_MGR.GetTexture("graphics/Player/PlayerMask_Resize.png"));

	direction = {0.f, 0.f};
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
	ResetCollision();

	SpriteGo::Update(deltaTime);
	for (int i = 0; i < rectArr.size(); i++)
	{
		rectArr[i].setPosition(position);
	}
	CollideCheck();

	//test
	MoveTest(deltaTime);
	//MovePlayer(deltaTime);

	//if (INPUT_MGR.GetKeyDown(sf::Keyboard::Z))
	//{
	//	Bullet* bullet = poolBullets.Get();
	//	bullet->Fire(position, direction, 500.f);
	//}
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

void Player::MoveTest(float deltaTime)
{
	std::cout << "Top: " << ((topCollision) ? "O " : "X ")
		<< "Bottom: " << ((bottomCollision) ? "O " : "X ")
		<< "Left: " << ((leftCollision) ? "O " : "X ")
		<< "Right: " << ((rightCollision) ? "O " : "X ")
		<< std::endl;

	direction.x = INPUT_MGR.GetAxisRaw(Axis::Horizontal);
	direction.y = INPUT_MGR.GetAxisRaw(Axis::Vertical);

	if (topCollision)
	{
	}
	if (bottomCollision)
	{
	}
	if (leftCollision)
	{
	}
	if (rightCollision)
	{
	}
	SetPosition(position + direction * speed * deltaTime);
}

void Player::Draw(sf::RenderWindow& window)
{
	for (int i = 0; i < newTileBounds.size(); ++i)
	{
		window.draw(newTileBounds[i]);
	}

	SpriteGo::Draw(window);

	//for (int i = 0; i < rectArr.size(); i++)
	//{
	//	window.draw(rectArr[i]);
	//}
}

void Player::MovePlayer(float deltaTime)
{
	velocity += gravity * gravityAccel * deltaTime;
	horizonRaw = INPUT_MGR.GetAxisRaw(Axis::Horizontal);

	if (topCollision)
	{
	}
	if (bottomCollision)
	{
		velocity = 0.f;
		jump = false;
		djump = false;
	}
	if (leftCollision)
	{
	}
	if (rightCollision)
	{
	}


	//점프 임시임!!
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::LShift))
	{
		std::cout << "jump!" << std::endl;
		velocity = -jumpForce;
		jump = true;
	}
	
	position.x += horizonRaw * speed * deltaTime;
	position.y += velocity * deltaTime;

	SetPosition(position);
}

void Player::CollideCheck()
{
	sf::Vector2f tileSize = tileMap->GetTileSize();
	sf::Vector2i playerTile = (sf::Vector2i)(position / tileSize.x);

	//타일 개수
	sf::Vector2i tileMatrix = tileMap->GetTileMatrix();
	//검사할 타일
	std::vector<sf::Vector2i> nearTiles;
	nearTiles.push_back({ playerTile.x, playerTile.y - 1 });
	nearTiles.push_back({ playerTile.x, playerTile.y + 1 });
	nearTiles.push_back({ playerTile.x - 1, playerTile.y });
	nearTiles.push_back({ playerTile.x + 1, playerTile.y });
	nearTiles.push_back({ playerTile.x, playerTile.y });
	nearTiles.push_back({ playerTile.x + 1, playerTile.y - 1 });
	nearTiles.push_back({ playerTile.x - 1, playerTile.y - 1 });
	nearTiles.push_back({ playerTile.x + 1, playerTile.y + 1 });
	nearTiles.push_back({ playerTile.x - 1, playerTile.y + 1 });
	newTileBounds.clear();

	for (int i = 0; i < nearTiles.size(); i++)
	{

		int tileIndex = tileMap->GetTileIndex(nearTiles[i]);
		if (tileIndex < 0 || tileIndex >= tileMatrix.x * tileMatrix.y)
			continue;

		Tile& tile = tileMap->tiles[tileIndex];
		if (tile.type == Tile::Types::None)
			continue;
		
		sf::FloatRect tileBounds(tile.position.x, tile.position.y, tileSize.x, tileSize.y);
		sf::RectangleShape shape;
		shape.setPosition(tile.position);
		shape.setSize(tileSize);
		shape.setFillColor(sf::Color::Blue);
		newTileBounds.push_back(shape);

		sf::FloatRect playerBounds = sprite.getGlobalBounds();
		sf::FloatRect overlap;

		//float == 비교 고쳐야함!!!!
		//https://noobtuts.com/cpp/compare-float-values 참고해볼것

		if (playerBounds.intersects(tileBounds, overlap))
		{
			if (overlap.width > overlap.height) //위 아래
			{
				if (playerBounds.top == overlap.top)
				{
					//상
					topCollision = true;
					position.y = tileBounds.top + tileBounds.height + playerBounds.height;
				}
				if (playerBounds.top + playerBounds.height == overlap.top + overlap.height)
				{
					//하
					bottomCollision = true;
					position.y = tileBounds.top;
				}
			}
			if (overlap.width < overlap.height) //좌 우
			{
				if (playerBounds.left == overlap.left)
				{
					//좌
					leftCollision = true;
					position.x = tileBounds.left + tileBounds.width + playerBounds.width * 0.5f;
				}
				if (playerBounds.left + playerBounds.width == overlap.left + overlap.width)
				{
					//우
					rightCollision = true;
					position.x = tileBounds.left - playerBounds.width * 0.5f;
				}
			}
		}
	}
}

void Player::ResetCollision()
{
	topCollision = false;
	bottomCollision = false;
	leftCollision = false;
	rightCollision = false;
}


/*
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
*/