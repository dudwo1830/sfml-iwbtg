#include "stdafx.h"
#include "Player.h"
#include "TileMap.h"
#include "InputMgr.h"
#include "ResourceMgr.h"
#include "Bullet.h"
#include "SceneMgr.h"
#include "SceneTitle.h"
#include "Framework.h"

#include "Collider.h"
Player::Player(const std::string& textureId, const std::string& name)
	:SpriteGo(textureId, name)
{
}

Player::~Player()
{
}

void Player::Init()
{
	hitBox.setFillColor(sf::Color::Magenta);
	hitBox.setSize({11.f, 21.f});
	Utils::SetOrigin(hitBox, Origins::BC);

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Player/Idle.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Player/Jump.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Player/Fall.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Player/Run.csv"));
	animation.SetTarget(&sprite);

	SetOrigin(Origins::BC);

	ObjectPool<Bullet>* ptr = &poolBullets;
	poolBullets.OnCreate = [ptr, this](Bullet* bullet) {
		bullet->SetTileMap(tileMap);
		bullet->pool = ptr;
		bullet->SetOrigin(Origins::MC);
	};
	poolBullets.Init();
}

void Player::Release()
{
	poolBullets.Release();
}

void Player::Reset()
{
	animation.Play("Idle");
	
	velocity = {0.f, 0.f};
	jump = false;
	djump = false;
	wallClimb = false;

	flipX = false;

	isAlive = true;

	SetOrigin(origin);
	ResetCollision();

	//Bullet
	for (auto bullet : poolBullets.GetUseList())
	{
		SCENE_MGR.GetCurrentScene()->RemoveGo(bullet);
	}
	poolBullets.Clear();
}

void Player::Update(float deltaTime)
{
	if (!isAlive)
	{
		return;
	}

	ResetCollision();
	animation.Update(deltaTime);
	prevPos = position;

	//SpriteGo::Update(deltaTime);
	velocity.y += gravity * gravityAccel * deltaTime;
	velocity.x = INPUT_MGR.GetAxisRaw(Axis::Horizontal);

	if (velocity.x != 0.f)
	{
		bool flip = velocity.x < 0.f;
		SetFlipX(flip);
	}

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::LShift))
	{
		Jump();
	}

	if (INPUT_MGR.GetKeyUp(sf::Keyboard::LShift))
	{
		if (!djump && velocity.y < 0.f)
		{
			velocity.y = 0.f;
		}
	}

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::F4))
	{
		testMode = !testMode;
	}
	if (testMode)
	{
		MoveTest(deltaTime);
	}
	else
	{
		MovePlayer(deltaTime);
	}


	SetPosition(position);
	hitBox.setPosition(position);
	playerBounds = hitBox.getGlobalBounds();

	CollideWindowCheck();
	CollideCheck();

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Z))
	{
		Shoot();
	}
	UpdateAnimation();
}

void Player::Draw(sf::RenderWindow& window)
{
	for (int i = 0; i < newTileBounds.size(); ++i)
	{
		window.draw(newTileBounds[i]);
	}
	SpriteGo::Draw(window);
	if (testMode)
	{
		window.draw(hitBox);
	}
}

void Player::SetFlipX(bool flip)
{
	flipX = flip;
	sf::Vector2f scale = sprite.getScale();
	scale.x = (!flipX) ? abs(scale.x) : -abs(scale.x);
	sprite.setScale(scale);
}

void Player::SetWallClimb(bool wallClimb)
{
	this->wallClimb = wallClimb;
	if (wallClimb)
	{
		jump = false;
		djump = false;
	}
}

Collider Player::GetCollider()
{
	return Collider(hitBox);
}

void Player::UpdateAnimation()
{
	std::string currentAnimation = animation.GetCurrentClipId();
	if (currentAnimation == "Idle")
	{
		if (bottomCollision && velocity.x != 0.f)
			animation.Play("Run");
		else if (velocity.y < 0.f)
			animation.Play("Jump");
		else if(velocity.y > 0.f)
			animation.Play("Fall");
	}
	else if (currentAnimation == "Run")
	{
		if (bottomCollision && velocity.x == 0.f)
			animation.Play("Idle");
		else if (!bottomCollision && velocity.y < 0.f)
			animation.Play("Jump");
	}
	else if (currentAnimation == "Jump")
	{
		if(!bottomCollision && velocity.y > 0.f)
			animation.Play("Fall");
	}
	else if (currentAnimation == "Fall")
	{
		if (bottomCollision)
			animation.Play((velocity.x == 0.f) ? "Idle" : "Run");
		else if (velocity.y < 0.f)
			animation.Play("Jump");
	}	
}

void Player::MoveTest(float deltaTime)
{
	velocity.x = INPUT_MGR.GetAxisRaw(Axis::Horizontal);
	velocity.y = INPUT_MGR.GetAxisRaw(Axis::Vertical);
	position += velocity * speed * deltaTime;
}

void Player::MovePlayer(float deltaTime)
{
	position.x += velocity.x * speed * deltaTime;
	position.y += velocity.y * deltaTime;
}

const sf::FloatRect& Player::GetBounds()
{
	return hitBox.getGlobalBounds();
}

void Player::Jump()
{
	wallClimb = false;
	if (!jump)
	{
		velocity.y = -jumpForce;
		jump = true;
	}
	else if (jump && !djump)
	{
		velocity.y = -djumpForce;
		djump = true;
	}
}

void Player::CollideWindowCheck()
{
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSize();
	if (position.y - playerBounds.height <= 0) //Top
		position = { position.x, 0.f + playerBounds.height };
	if (position.y >= windowSize.y - playerBounds.height) //Bottom
		position = { position.x, windowSize.y - playerBounds.height };
	if (position.x - playerBounds.width * 0.5f <= 0) //Left
		position = { 0.f + playerBounds.width * 0.5f, position.y };
	if (position.x >= windowSize.x - playerBounds.width * 0.5f) //Right
		position = { windowSize.x - playerBounds.width * 0.5f, position.y };
}

void Player::CollideCheck()
{
	sf::Vector2f tileSize = tileMap->GetTileSize();
	sf::Vector2i playerTile = (sf::Vector2i)( position / tileSize.x);

	sf::Vector2i tileMatrix = tileMap->GetTileMatrix();

	std::vector<sf::Vector2i> nearTiles;
	nearTiles.push_back({ playerTile.x, playerTile.y - 1 });
	nearTiles.push_back({ playerTile.x, playerTile.y + 1 });
	nearTiles.push_back({ playerTile.x - 1, playerTile.y });
	nearTiles.push_back({ playerTile.x + 1, playerTile.y });
	nearTiles.push_back(playerTile);
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
		if (tile.type == Tile::Type::None)
			continue;

		sf::FloatRect tileBounds(tile.position.x, tile.position.y, tileSize.x, tileSize.y);
		sf::FloatRect overlap;

		//타일탐색 시각화
		sf::RectangleShape shape;
		shape.setPosition(tile.position);
		shape.setSize(tileSize);
		shape.setFillColor(sf::Color::Blue);
		newTileBounds.push_back(shape);


		if (tileBounds.intersects(playerBounds, overlap))
		{
			if (tile.type == Tile::Type::Killer)
			{
				Die();
				return;
			}

			if (overlap.width > overlap.height)
			{
				if (Utils::CompareFloat(playerBounds.top, overlap.top))
				{
					topCollision = true;
				}
				else if (Utils::CompareFloat(playerBounds.top + playerBounds.height, overlap.top + overlap.height))
				{
					bottomCollision = true;
					//velocity.y = 0.f;
					//jump = false;
					//djump = false;
				}
			}
			else if (overlap.width < overlap.height)
			{
				if (Utils::CompareFloat(playerBounds.left, overlap.left))
				{
					leftCollision = true;
					//velocity.x = 0.f;
				}
				else if (Utils::CompareFloat(playerBounds.left + playerBounds.width, overlap.left + overlap.width))
				{
					rightCollision = true;
					//velocity.x = 0.f;
				}
			}
		}
	}
	
	if (topCollision && leftCollision)
	{
		position = prevPos;
	}
	else if (topCollision && rightCollision) 
	{
		position = prevPos;
	}
	else if (bottomCollision && leftCollision)
	{
		velocity.y = 0.f;
		position = prevPos;
	}
	else if (bottomCollision && rightCollision)
	{
		if (velocity.y > 0.1f || velocity.y < 0.1f)
		{
			
		}
		else
		{
			velocity.y = 0.f;
		}
		position = prevPos;
	}
	else if (topCollision)
	{
		position.y = prevPos.y;
	}
	else if (bottomCollision)
	{
		velocity.y = 0.f;
		position.y = prevPos.y;
		jump = false;
		djump = false;
	}
	else if (leftCollision)
	{
		position.x = prevPos.x;
	}
	else if (rightCollision)
	{
		position.x = prevPos.x;
	}


	//std::cout
	//	<< "Jump: " << ((jump) ? "O " : "X ")
	//	<< "dJump: " << ((djump) ? "O " : "X ")
	//	<< "wallClimb: " << ((wallClimb) ? "O " : "X ")
	//	<< "Top: " << ((topCollision) ? "O " : "X ")
	//	<< "Bottom: " << ((bottomCollision) ? "O " : "X ")
	//	<< "Left: " << ((leftCollision) ? "O " : "X ")
	//	<< "Right: " << ((rightCollision) ? "O " : "X ")
	//	<< "player pos: " << position.x << ", " << position.y
	//	<< std::endl;
}

void Player::ResetCollision()
{
	topCollision = false;
	bottomCollision = false;
	leftCollision = false;
	rightCollision = false;
}

void Player::Shoot()
{
	Bullet* bullet = poolBullets.Get();
	sf::Vector2f bulletPos = { position.x, position.y - playerBounds.height / 2.f};
	bullet->Fire(bulletPos, { (flipX) ? -1.f : 1.f, 0.f }, 400.f);
	Scene* scene = SCENE_MGR.GetCurrentScene();
	SceneTitle* sceneTitle = dynamic_cast<SceneTitle*>(scene);
	if (sceneTitle != nullptr)
	{
		bullet->SetTileMap(tileMap);
		sceneTitle->AddGo(bullet);
	}
}

void Player::Die()
{
	isAlive = false;
}
