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

void Player::SetPosition(const sf::Vector2f& position)
{
	SpriteGo::SetPosition(position);
	collider->SetPosition(position);
	hitBox.setPosition(position);
}

void Player::Init()
{
}

void Player::Release()
{
	poolBullets.Release();
}

void Player::Reset()
{
	hitBox.setFillColor(sf::Color::Magenta);
	hitBox.setSize(hitBoxSize);
	Utils::SetOrigin(hitBox, Origins::BC);
	hitBox.setPosition(GetPosition());

	collider->SetColor(sf::Color::Red);
	collider->SetSize(hitBoxSize);
	collider->SetOrigin(Origins::BC);

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Player/Idle.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Player/Jump.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Player/Fall.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Player/Run.csv"));
	animation.SetTarget(&sprite);

	SetOrigin(Origins::BC);

	animation.Play("Idle");
	
	velocity = {0.f, 0.f};
	jump = false;
	djump = false;
	wallClimb = false;

	flipX = false;

	isAlive = true;

	SetOrigin(origin);
	ResetCollision();

	ObjectPool<Bullet>* ptr = &poolBullets;
	poolBullets.OnCreate = [ptr, this](Bullet* bullet) {
		bullet->SetTileMap(tileMap);
		bullet->pool = ptr;
		bullet->SetOrigin(Origins::MC);
	};
	poolBullets.Init();

	////Bullet
	//for (auto bullet : poolBullets.GetUseList())
	//{
	//	SCENE_MGR.GetCurrentScene()->RemoveGo(bullet);
	//}
	//poolBullets.Clear();
}

void Player::Update(float deltaTime)
{
	if (!isAlive)
	{
		return;
	}

	animation.Update(deltaTime);
	prevPos = position;

	float h = INPUT_MGR.GetAxisRaw(Axis::Horizontal);
	//Flip
	if (velocity.x != 0.f)
	{
		bool flip = velocity.x < 0.f;
		SetFlipX(flip);
	}

	//SetTest
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::F4))
	{
		testMode = !testMode;
	}

	//Jump
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

	if (testMode)
	{
		float testSpeed = speed;
		if (INPUT_MGR.GetKey(sf::Keyboard::Num1))
		{
			testSpeed *= 2;
		}
		else if (INPUT_MGR.GetKey(sf::Keyboard::Num2))
		{
			testSpeed /= 3;
		}
		else if (INPUT_MGR.GetKey(sf::Keyboard::Num3))
		{
			testSpeed /= 10;
		}
		velocity.x = h * testSpeed;
		velocity.y = INPUT_MGR.GetAxisRaw(Axis::Vertical) * testSpeed;
	}
	else
	{
		velocity.x = h * speed;
		velocity.y += gravityAccel * deltaTime;
	}


	SetPosition(position + velocity * deltaTime);

	//ResetCollision();
	//CollideWindow();
	//CollideCheck();
	UpdateAnimation();

	//if (rightCollision || leftCollision)
	//{
	//	position.x = prevPos.x;
	//}
	//if (!rightCollision && !leftCollision)
	//{
	//	wallClimb = false;
	//}
	//if (topCollision)
	//{
	//	velocity.y = 0.f;
	//	position.y = prevPos.y;
	//}
	//if (bottomCollision)
	//{
	//	velocity.y = 0.f;
	//	position.y = prevPos.y;
	//	jump = false;
	//	djump = false;
	//}
	//if (!bottomCollision && !wallClimb)
	//{
	//	jump = true;
	//}
	//SetPosition(position);

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Z))
	{
		Shoot();
	}
}

void Player::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
	if (testMode)
	{
		for (int i = 0; i < newTileBounds.size(); ++i)
		{
			window.draw(newTileBounds[i]);
		}
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

void Player::UpdateAnimation()
{
	std::string currentAnimation = animation.GetCurrentClipId();
	if (currentAnimation == "Idle")
	{
		if (bottomCollision && velocity.x != 0.f)
			animation.Play("Run");
		else if (!bottomCollision && velocity.y < 0.f)
			animation.Play("Jump");
		else if(!bottomCollision && velocity.y > 0.f)
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
		if (!bottomCollision && velocity.y > 0.f)
			animation.Play("Fall");
		else if (bottomCollision)
			animation.Play("Idle");
	}
	else if (currentAnimation == "Fall")
	{
		if (bottomCollision)
			animation.Play((velocity.x == 0.f) ? "Idle" : "Run");
		else if (!bottomCollision && velocity.y < 0.f)
			animation.Play("Jump");
	}	
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

void Player::CollideWindow()
{
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSize();
	if (position.y - playerBounds.height <= 0) //Top
		position = { position.x, 0.f + playerBounds.height };
	if (position.y >= windowSize.y) //Bottom
		Die();
	if (position.x - playerBounds.width * 0.5f <= 0) //Left
		position = { 0.f + playerBounds.width * 0.5f, position.y };
	if (position.x >= windowSize.x - playerBounds.width * 0.5f) //Right
		position = { windowSize.x - playerBounds.width * 0.5f, position.y };
}

void Player::CollideCheck()
{
	sf::Vector2f tileSize = tileMap->GetTileSize();
	sf::Vector2i playerTile = (sf::Vector2i)( position / tileSize.x);
	playerBounds = hitBox.getGlobalBounds();
	sf::FloatRect playerBounds2 = hitBox.getGlobalBounds();
	playerBounds2.left += playerBounds2.width * 0.25f;
	playerBounds2.width *= 0.5;

	sf::Vector2i tileMatrix = tileMap->GetTileMatrix();

	std::vector<sf::Vector2i> nearTiles;
	for (int xOffset = -1; xOffset <= 1; xOffset++)
	{
		for (int yOffset = -1; yOffset <= 1; yOffset++)
		{
			nearTiles.push_back({ playerTile.x + xOffset, playerTile.y + yOffset });
		}
	}
	//nearTiles.push_back({ playerTile.x, playerTile.y - 1 });
	//nearTiles.push_back({ playerTile.x, playerTile.y + 1 });
	//nearTiles.push_back({ playerTile.x - 1, playerTile.y });
	//nearTiles.push_back({ playerTile.x + 1, playerTile.y });
	//nearTiles.push_back(playerTile);
	//nearTiles.push_back({ playerTile.x + 1, playerTile.y - 1 });
	//nearTiles.push_back({ playerTile.x - 1, playerTile.y - 1 });
	//nearTiles.push_back({ playerTile.x + 1, playerTile.y + 1 });
	//nearTiles.push_back({ playerTile.x - 1, playerTile.y + 1 });
	newTileBounds.clear();

	for (int i = 0; i < nearTiles.size(); i++)
	{
		int tileIndex = tileMap->GetTileIndex(nearTiles[i]);
		if (tileIndex < 0 || tileIndex >= tileMatrix.x * tileMatrix.y)
			continue;

		Tile& tile = tileMap->tiles[tileIndex];
		if (tile.type == Tile::Type::None)
			continue;

		sf::FloatRect tileBounds = tile.collider->GetBounds();
		//sf::FloatRect tileBounds(tile.position.x, tile.position.y, tileSize.x, tileSize.y);
		sf::FloatRect overlap;

		//타일탐색 시각화
		sf::RectangleShape shape;
		shape.setPosition(tile.position);
		shape.setSize(tileSize);
		shape.setFillColor(sf::Color::Blue);
		newTileBounds.push_back(shape);

		

		//if (tileBounds.intersects(playerBounds2, overlap))
		//{
		//	if (overlap.width > overlap.height)
		//	{
		//		if (Utils::CompareFloat(playerBounds2.top, overlap.top))
		//		{
		//			topCollision = true;
		//		}
		//		else if (Utils::CompareFloat(playerBounds2.top + playerBounds2.height, overlap.top + overlap.height))
		//		{
		//			bottomCollision = true;
		//		}
		//	}
		//}
		//if (tileBounds.intersects(playerBounds, overlap))
		//{
		//	if (overlap.width < overlap.height)
		//	{
		//		if (Utils::CompareFloat(playerBounds.left, overlap.left))
		//		{
		//			leftCollision = true;
		//		}
		//		else if (Utils::CompareFloat(playerBounds.left + playerBounds.width, overlap.left + overlap.width))
		//		{
		//			rightCollision = true;
		//		}
		//	}
		//}
	}

	//std::cout
	//	<< "Jump: " << ((jump) ? "O " : "X ")
	//	<< "dJump: " << ((djump) ? "O " : "X ")
	//	<< "wallClimb: " << ((wallClimb) ? "O " : "X ")
	//	<< "Top: " << ((topCollision) ? "O " : "X ")
	//	<< "Bottom: " << ((bottomCollision) ? "O " : "X ")
	//	<< "Left: " << ((leftCollision) ? "O " : "X ")
	//	<< "Right: " << ((rightCollision) ? "O " : "X ")
	//	<< "player pos: " << playerBounds.left << ", " << playerBounds.top
	//	<< " veloc: " << velocity.x << ", " << velocity.y
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
	bullet->Fire(bulletPos, { (flipX) ? -1.f : 1.f, 0.f }, bulletSpeed);
	Scene* scene = SCENE_MGR.GetCurrentScene();
	//SceneTitle* sceneTitle = dynamic_cast<SceneTitle*>(scene);
	if (scene != nullptr)
	{
		bullet->SetTileMap(tileMap);
		scene->AddGo(bullet);
	}
}

void Player::Die()
{
	isAlive = false;
	for (auto bullet : poolBullets.GetUseList())
	{
		SCENE_MGR.GetCurrentScene()->RemoveGo(bullet);
	}
	poolBullets.Clear();
}
