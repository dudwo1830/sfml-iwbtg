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
	Player* player = (Player*)AddGo(new Player("", "Player"));
	for (auto go : gameObjects)
	{
		go->Init();
	}
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
	
	//if (INPUT_MGR.GetKeyDown(sf::Keyboard::Escape))
	//{
	//	SCENE_MGR.ChangeScene(SceneId::Game);
	//}
}

void SceneTitle::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
