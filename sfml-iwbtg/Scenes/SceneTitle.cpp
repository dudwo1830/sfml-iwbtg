#include "stdafx.h"
#include "SceneTitle.h"
#include "InputMgr.h"
#include "SceneMgr.h"
#include "ResourceMgr.h"
#include "Framework.h"
#include "SpriteGo.h"
#include "TextGo.h"

//test
#include "Player.h"
#include "TileMap.h"

SceneTitle::SceneTitle()
	:Scene(SceneId::Title)
{
	resourceListPath = "scripts/SceneTitleResourceList.csv";
}

SceneTitle::~SceneTitle()
{
	Release();
}

void SceneTitle::Init()
{
	Release();
	tileMap = (TileMap*)AddGo(new TileMap("graphics/tileMap.png", "Tile Map"));
	player = (Player*)AddGo(new Player("", "Player"));

	for (auto go : gameObjects)
	{
		go->Init();
	}
	tileMap->Load("map/map1.csv");
	tileMap->SetOrigin(Origins::TL);

	player->SetTileMap(tileMap);
}

void SceneTitle::Release()
{
	for (auto go : gameObjects)
	{
		//go->Release();
		delete go;
	}
}

void SceneTitle::Enter()
{
	Scene::Enter();
	//sf::Vector2f windowSize = FRAMEWORK.GetWindowSize();

	sf::Vector2i startTilePos = { 1, 17 };
	sf::Vector2f tileSize = tileMap->GetTileSize();
	player->SetPosition({ startTilePos.x * tileSize.x, startTilePos.y * tileSize.y });
}

void SceneTitle::Exit()
{
	Scene::Exit();
}

void SceneTitle::Update(float dt)
{
	Scene::Update(dt);
	
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Escape))
	{
		SCENE_MGR.ChangeScene(SceneId::Game);
	}
}

void SceneTitle::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

