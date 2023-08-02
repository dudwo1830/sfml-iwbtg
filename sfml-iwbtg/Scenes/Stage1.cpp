#include "stdafx.h"
#include "Stage1.h"
#include "InputMgr.h"
#include "SceneMgr.h"
#include "ResourceMgr.h"
#include "Framework.h"
#include "SpriteGo.h"
#include "TextGo.h"

//test
#include "rapidcsv.h"
#include "Player.h"
#include "TileMap.h"
#include "Obstacle.h"
#include "Bullet.h"
#include "Spike.h"
#include "SaveLoadMgr.h"

Stage1::Stage1()
	:Scene(SceneId::Stage1)
{
	resourceListPath = "scripts/Stage1ResourceList.csv";
}

Stage1::~Stage1()
{
	Release();
}

void Stage1::Init()
{
	Release();
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSize();
	sf::Vector2f centerPos = windowSize * 0.5f;

	worldView.setSize(windowSize);
	worldView.setCenter(centerPos);
	uiView.setSize(windowSize);
	uiView.setCenter(centerPos);

	//Background
	VertexArrayGo* background = CreateBackground({ 1, 1 }, windowSize);
	AddGo(background);
	background->SetOrigin(Origins::TL);
	background->SetPosition(0.f, 0.f);
	background->sortLayer = -99;

	//Map
	tileMap = (TileMap*)AddGo(new TileMap("graphics/tileMap.png", "TileMap"));
	tileMap->SetSpikeList(&spikeList);
	tileMap->Load("map/Stage1.csv");
	tileMap->SetOrigin(Origins::TL);
	sf::Vector2f tileSize = tileMap->GetTileSize();
	LoadObs("map/Stage1-obs.csv", tileSize);

	//GameOver
	gameOver = (SpriteGo*)AddGo(new SpriteGo("graphics/Misc/GameOver.png", "GameOver"));
	gameOver->SetActive(false);
	gameOver->SetOrigin(Origins::MC);
	gameOver->SetPosition(centerPos);
	gameOver->sortLayer = 99;

	//Player
	player = (Player*)AddGo(new Player("", "Player"));
	player->SetTileMap(tileMap);
	player->SetCollider(new Collider());

	AddGo((GameObject*)player->GetCollider());
	for (auto& go : spikeList)
	{
		AddGo((GameObject*)go);
	}
	for (auto& go : gameObjects)
	{
		go->Init();
	}
}

void Stage1::Release()
{
	for (auto go : gameObjects)
	{
		//go->Release();
		delete go;
	}
}

void Stage1::Enter()
{
	Scene::Enter();
	gameOver->SetActive(false);

	player->SetPosition(Variables::CheckPoint);
	player->SetFlipX(player->GetFlipX());
}

void Stage1::Exit()
{
	Scene::Exit();
}

void Stage1::Update(float dt)
{
	Scene::Update(dt);
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Escape))
	{
		SCENE_MGR.ChangeScene(SceneId::Stage2);
		return;
	}

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::F5))
	{
		std::cout << SAVELOAD_MGR.GetCurrentFileName() << std::endl;
	}

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::R))
	{
		Enter();
		return;
	}

	if (!player->GetAlive())
	{
		Variables::CheckPoint = { 1 * tileMap->GetTileSize().x, 15 * tileMap->GetTileSize().y };
		if (!gameOver->GetActive())
		{
			gameOver->SetActive(true);
		}
		return;
	}
	
	Collider* playerCollider = player->GetCollider();
	std::vector<Tile*> tiles = tileMap->GetNearTiles(player->GetPosition());
	for (int i = 0; i < tiles.size(); i++)
	{
		if (tiles[i]->type == Tile::Type::None)
		{
			continue;
		}
		if (playerCollider->CheckCollision(*tiles[i]->collider))
		{
			playerCollider->ResolveCollision(*tiles[i]->collider);
		}
	}

	sf::FloatRect playerBounds = player->GetBounds();
	for (auto& obs : obsList)
	{
		switch (obs->GetType())
		{
		case Obstacle::Type::None:
			break;
		case Obstacle::Type::Item:
			obs->CollideCheck(player->GetHitBoxBounds());
			break;
		case Obstacle::Type::Save:
			for (auto& bullet : player->poolBullets.GetUseList())
			{
				obs->CollideCheck(bullet->GetBounds());
			}
			break;
		case Obstacle::Type::WallClimb:
			obs->CollideCheck(player->GetBounds());
			break;
		case Obstacle::Type::Block:
			obs->CollideCheck(player->GetHitBoxBounds());
			break;
		case Obstacle::Type::Trap:
			obs->CollideCheck(player->GetHitBoxBounds());
			break;
		case Obstacle::Type::Clear:
			obs->CollideCheck(player->GetHitBoxBounds());
			break;
		default:
			break;
		}
	}

	for (auto& spike : spikeList)
	{
		if (spike->isColliding(player->GetHitBox()))
		{
			player->Die();
			return;
		}
	}
}

void Stage1::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

VertexArrayGo* Stage1::CreateBackground(const sf::Vector2f& tileMatrix, const sf::Vector2f& tileSize, const sf::Vector2f& texSize, const std::string& textureId)
{
	VertexArrayGo* background = new VertexArrayGo(textureId, "Background");
	sf::Vector2f startPos = { 0,0 };

	sf::VertexArray& vertexArray = background->GetVertexArray();
	background->SetPrimitiveType(sf::Quads);
	background->ReSize(tileMatrix.x * tileMatrix.y * 4);

	sf::Vector2f offsets[4] =
	{
		{0.f,0.f},
		{tileSize.x,0.f},
		{tileSize.x,tileSize.y },
		{0.f,tileSize.y}
	};

	sf::Vector2f texOffsets[4] =
	{
		{0.f,0.f},
		{texSize.x,0.f},
		{texSize.x,texSize.y },
		{0.f,texSize.y}
	};

	sf::Vector2f currPos = startPos;
	for (int i = 0; i < tileMatrix.y; ++i)
	{
		for (int j = 0; j < tileMatrix.x; ++j)
		{
			int tileIndex = tileMatrix.x * i + j;
			for (int k = 0; k < 4; ++k)
			{
				int vertexIndex = tileIndex * 4 + k;
				sf::Color color = (vertexIndex < 2) ? sf::Color::White : sf::Color(98, 107, 141);
				vertexArray[vertexIndex].position = currPos + offsets[k];
				vertexArray[vertexIndex].color = color;
			}
			currPos.x += tileSize.x;
		}
		currPos.x = startPos.x;
		currPos.y += tileSize.y;
	}
	return background;
}

bool Stage1::LoadObs(const std::string& filePath, sf::Vector2f tileSize)
{
	rapidcsv::Document map(filePath, rapidcsv::LabelParams(-1, -1));
	for (int i = 1; i < map.GetRowCount(); i++)
	{
		//Obstacle
		Obstacle::Type type = (Obstacle::Type)map.GetCell<int>(0, i);
		bool isHide = (map.GetCell<int>(6, i) == 0) ? false : true;

		//SpriteGo
		std::string id = map.GetCell<std::string>(1, i);
		std::string textureId = map.GetCell<std::string>(2, i);
		bool useTileSize = map.GetCell<int>(3, i);
		float leftValue = map.GetCell<float>(4, i);
		float topValue = map.GetCell<float>(5, i);
		bool defaultHide = map.GetCell<int>(6, i);
		int sort = i;
		if (map.GetCell<std::string>(7, i) != "")
			sort = std::stoi(map.GetCell<std::string>(7, i));

		sf::Vector2f position = { leftValue, topValue };
		if (useTileSize)
		{
			position.x *= tileSize.x;
			position.y *= tileSize.y;
		}

		Obstacle* obs = (Obstacle*)AddGo(new Obstacle(textureId, id));
		obs->SetPosition(position);
		obs->SetType(type);
		obs->SetDefaultHide(defaultHide);
		obs->sortLayer = sort;

		switch (type)
		{
		case Obstacle::Type::None:
			break;
		case Obstacle::Type::Item:
			obs->SetCollideEvent([this, obs]() {
				player->SetDJump(false);
				obs->SetHideTime(2.f);
				obs->SetHide(true);
				});
			break;
		case Obstacle::Type::Save:
			obs->SetCollideEvent([this, obs]() {
				Variables::CheckPoint = player->GetPosition();
				obs->SetHideTime(0.5f);
				obs->SetHide(true);
				SaveData();
				});
			break;
		case Obstacle::Type::WallClimb:
			if (obs->GetName() == "WallJumpL")
			{
				obs->SetCollideEvent([this]() {
					player->SetWallClimb(true);
					});
			}
			else if (obs->GetName() == "WallJumpR")
			{
				obs->SetCollideEvent([this]() {
					player->SetWallClimb(true);
					});
			}
			break;
		case Obstacle::Type::Block:
			obs->SetCollideEvent([this]() {
				player->SetPosition(player->GetPrevPos());
				});
			break;
		case Obstacle::Type::Trap:
			player->Die();
			break;
		case Obstacle::Type::Clear:
			obs->SetCollideEvent([this]() {
				Variables::CheckPoint = { defaultCheckPointTile.x * tileMap->GetTileSize().x, defaultCheckPointTile.y * tileMap->GetTileSize().y };
				SCENE_MGR.ChangeScene(SceneId::Stage2);
				});
		default:
			break;
		}

		obsList.push_back(obs);
	}
	return true;
}