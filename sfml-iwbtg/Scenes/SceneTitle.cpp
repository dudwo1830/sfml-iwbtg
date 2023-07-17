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
	player = (Player*)AddGo(new Player("", "Player"));
	tileMap = (TileMap*)AddGo(new TileMap("graphics/tileMap.png", "Tile Map"));
	TileMap* miscMap = (TileMap*)AddGo(new TileMap("graphics/wallJump.png", "Tall Jump"));

	for (auto go : gameObjects)
	{
		go->Init();
	}
	tileMap->Load("map/map1.csv");
	miscMap->Load("map/map1-misc.csv");
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

	sf::Vector2f windowSize = FRAMEWORK.GetWindowSize();
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

