#include "stdafx.h"
#include "Player.h"
#include "TileMap.h"
#include "InputMgr.h"
#include "ResourceMgr.h"
#include "Bullet.h"
#include "SceneMgr.h"
#include <SceneTitle.h>
#include <Framework.h>

Player::Player(const std::string& textureId, const std::string& name)
	:SpriteGo(textureId, name)
{
}

Player::~Player()
{
}

void Player::Init()
{
	SpriteGo::Init();
	SetOrigin(Origins::BC);
	
	ObjectPool<Bullet>* ptr = &poolBullets;
	poolBullets.OnCreate = [ptr, this](Bullet* bullet) {
		bullet->SetTextureId("graphics/Player/Bullet.png");
		bullet->SetTileMap(tileMap);
		bullet->pool = ptr;
	};
	poolBullets.Init(5);
}

void Player::Release()
{
	poolBullets.Release();
}

void Player::Reset()
{
	SpriteGo::Reset();
	sprite.setTexture(*RESOURCE_MGR.GetTexture("graphics/Player/PlayerMask_Resize.png"));

	jump = false;
	djump = false;
	wallClimb = false;

	flipX = false;

	isAlive = true;

	SetOrigin(origin);
	ResetCollision();

	SwitchOutline(true);

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
	SpriteGo::Update(deltaTime);
	velocity.y += gravity * gravityAccel * deltaTime;
	velocity.x = INPUT_MGR.GetAxisRaw(Axis::Horizontal);

	if (velocity.x != 0.f)
	{
		//false�϶� ����
		bool flip = velocity.x < 0.f;
		SetFlipX(flip);
	}


	//������ �浹
	CollideWindowCheck();

	//�浹
	CollideCheck();

	if (testMode)
	{
		MoveTest(deltaTime);
	}
	else
	{
		MovePlayer(deltaTime);
	}

	//���� �̵��� ������
	SetPosition(position);

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::F4))
	{
		testMode = !testMode;
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::LShift))
	{
		if (!jump)
		{
			velocity.y = -jumpForce;
		}
		else if(jump && !djump)
		{
			velocity.y -= djumpForce;
		}
	}
	if (INPUT_MGR.GetKeyUp(sf::Keyboard::LShift))
	{
		if (velocity.y >= 0.f)
		{
			velocity.y = 0.f;
		}
	}

	if (INPUT_MGR.GetKey(sf::Keyboard::Z))
	{
		Shoot();
	}
	ResetCollision();
}

void Player::Draw(sf::RenderWindow& window)
{
	for (int i = 0; i < newTileBounds.size(); ++i)
	{
		window.draw(newTileBounds[i]);
	}
	SpriteGo::Draw(window);
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

bool Player::GetAlive() const
{
	return isAlive;
}

void Player::MoveTest(float deltaTime)
{
	std::cout
		<< "Jump: " << ((jump) ? "O " : "X ")
		<< "dJump: " << ((djump) ? "O " : "X ")
		<< "wallClimb: " << ((wallClimb) ? "O " : "X ")
		<< "Top: " << ((topCollision) ? "O " : "X ")
		<< "Bottom: " << ((bottomCollision) ? "O " : "X ")
		<< "Left: " << ((leftCollision) ? "O " : "X ")
		<< "Right: " << ((rightCollision) ? "O " : "X ")
		<< std::endl;

	velocity.x = INPUT_MGR.GetAxisRaw(Axis::Horizontal);
	velocity.y = INPUT_MGR.GetAxisRaw(Axis::Vertical);
	SetPosition(position + velocity * speed * deltaTime);
}

void Player::MovePlayer(float deltaTime)
{
	std::cout 
		<< "Jump: " << ((jump) ? "O " : "X ")
		<< "dJump: " << ((djump) ? "O " : "X ")
		<< "wallClimb: " << ((wallClimb) ? "O " : "X ")
		<< "Top: " << ((topCollision) ? "O " : "X ")
		<< "Bottom: " << ((bottomCollision) ? "O " : "X ")
		<< "Left: " << ((leftCollision) ? "O " : "X ")
		<< "Right: " << ((rightCollision) ? "O " : "X ")
		<< "player pos: " << position.x << ", " << position.y
		<< std::endl;

	position.x += velocity.x * speed * deltaTime;
	position.y += velocity.y * deltaTime;
}

void Player::Jump(float deltaTime)
{
	wallClimb = false;
	if (!jump)
	{
		velocity.y = -jumpForce;
		jump = true;
	}
	else if (!djump)
	{
		velocity.y = -djumpForce;
		djump = true;
	}
}

void Player::CollideWindowCheck()
{
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSize();
	sf::FloatRect playerBounds = sprite.getGlobalBounds();
	if (position.y - playerBounds.height <= 0) //Top
		position = { position.x, 0.f + playerBounds.height };
		//SetPosition(position.x, 0.f + playerBounds.height);
	if (position.y >= windowSize.y - playerBounds.height) //Bottom
		position = { position.x, windowSize.y - playerBounds.height };
	//SetPosition(position.x, windowSize.y - playerBounds.height);
	if (position.x - playerBounds.width * 0.5f <= 0) //Left
		position = { 0.f + playerBounds.width * 0.5f, position.y };
	//SetPosition(0.f + playerBounds.width * 0.5f, position.y);
	if (position.x >= windowSize.x - playerBounds.width * 0.5f) //Right
		position = { windowSize.x - playerBounds.width * 0.5f, position.y };
	//SetPosition(windowSize.x - playerBounds.width * 0.5f, position.y);
}

void Player::CollideCheck()
{
	sf::Vector2f tileSize = tileMap->GetTileSize();
	sf::FloatRect playerBounds = sprite.getGlobalBounds();
	sf::Vector2i playerTile = (sf::Vector2i)( position / tileSize.x);

	//Ÿ�� ����
	sf::Vector2i tileMatrix = tileMap->GetTileMatrix();

	//�˻��� Ÿ��
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
		if (tile.type == Tile::Types::None)
			continue;
		
		sf::FloatRect tileBounds(tile.position.x, tile.position.y, tileSize.x, tileSize.y);
		sf::FloatRect overlap;

		//Ÿ�� ����ǥ��
		sf::RectangleShape shape;
		shape.setPosition(tile.position);
		shape.setSize(tileSize);
		shape.setFillColor(sf::Color::Blue);
		newTileBounds.push_back(shape);

		if (tileBounds.intersects(playerBounds, overlap))
		{
			if (tile.type == Tile::Types::Killer)
			{
				Die();
				return;
			}

			if (overlap.width > overlap.height)
			{
				if (Utils::CompareFloat(playerBounds.top, overlap.top))
				{
					topCollision = true;
					velocity.y = 0.f;
					position.y = tileBounds.top + tileBounds.height + playerBounds.height + 0.f;
				}
				else if (Utils::CompareFloat(playerBounds.top + playerBounds.height, overlap.top + overlap.height))
				{
					bottomCollision = true;
					velocity.y = 0.f;
					jump = false;
					jumping = false;
					djump = false;
					position.y = tileBounds.top - 0.f;
				}
			}

			if (overlap.width < overlap.height)
			{
				if (Utils::CompareFloat(playerBounds.left, overlap.left))
				{
					for (int n = 0; n < tile.gimmicks.size(); n++)
					{
						if (tile.gimmicks[n] == Tile::Gimmick::WallClimbL)
						{
							//��Ÿ��
							wallClimb = true;
							jump = false;
							djump = false;
							break;
						}
					}
					leftCollision = true;
					velocity.x = 0.f;
					position.x = tileBounds.left + tileBounds.width + playerBounds.width * 0.5f + 0.f;
				}
				else if (Utils::CompareFloat(playerBounds.left + playerBounds.width, overlap.left + overlap.width))
				{
					for (int n = 0; n < tile.gimmicks.size(); n++)
					{
						if (tile.gimmicks[n] == Tile::Gimmick::WallClimbR)
						{
							//��Ÿ��
							wallClimb = true;
							jump = false;
							djump = false;
							break;
						}
					}
					rightCollision = true;
					velocity.x = 0.f;
					position.x = tileBounds.left - playerBounds.width * 0.5f - 0.f;
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

void Player::Shoot()
{
	Bullet* bullet = poolBullets.Get();
	//�¿�θ� �߻�
	sf::Vector2f bulletPos = { position.x, position.y - sprite.getGlobalBounds().height / 2.f};
	bullet->Fire(bulletPos, { (flipX) ? -1.f : 1.f, 0.f }, 500.f);
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
