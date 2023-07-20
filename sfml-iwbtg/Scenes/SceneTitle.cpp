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
#include "Save.h"

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
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSize();
	sf::Vector2f centerPos = windowSize * 0.5f;

	worldView.setSize(windowSize);
	worldView.setCenter(centerPos);
	uiView.setSize(windowSize);
	uiView.setCenter(centerPos);

	//Background
	VertexArrayGo* background = CreateBackground({ 1, 1 }, windowSize, {0.f, 0.f}, "");
	AddGo(background);
	background->SetOrigin(Origins::TL);
	background->SetPosition(0.f, 0.f);
	background->sortLayer = -1;

	//Map
	tileMap = (TileMap*)AddGo(new TileMap("graphics/tileMap.png", "Tile Map"));
	TileMap* wallClimbMap = (TileMap*)AddGo(new TileMap("graphics/wallClimbMap.png", "wallJump"));

	//GameOver
	SpriteGo* gameOver = (SpriteGo*)AddGo(new SpriteGo("graphics/misc/GameOver.png", "GameOver"));
	gameOver->SetActive(false);
	gameOver->SetOrigin(Origins::MC);
	gameOver->SetPosition(centerPos);
	gameOver->sortLayer = 100;

	//Save
	//파일입출력으로 하는게 좋아보임..
	Save* save = (Save*)AddGo(new Save("graphics/Blocks/SaveBlocker.png", "block"));
	save->SetPosition({18 * 32.f, 14 * 32.f});
	save->SetOrigin(Origins::TL);
	saveList.push_back(save);

	//Player
	player = (Player*)AddGo(new Player("graphics/Player/PlayerMask_Resize.png", "Player"));

	for (auto go : gameObjects)
	{
		go->Init();
	}

	tileMap->Load("map/map1.csv");
	tileMap->SetOrigin(Origins::TL);
	wallClimbMap->Load("map/map1-misc.csv");
	wallClimbMap->SetOrigin(Origins::TL);

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

	SpriteGo* gameOver = (SpriteGo*)FindGo("GameOver");
	gameOver->SetActive(false);

	sf::Vector2i startTilePos = { 1, 16 };
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

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::F2))
	{
		ShowGoOutline();
	}

	if (!player->GetAlive())
	{
		SpriteGo* gameOver = (SpriteGo*)FindGo("GameOver");
		gameOver->SetActive(true);
	}

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::R))
	{
		Enter();
	}
}

void SceneTitle::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);

}

VertexArrayGo* SceneTitle::CreateBackground(sf::Vector2f size, sf::Vector2f tileSize, sf::Vector2f texSize, std::string textureId)
{
	VertexArrayGo* background = new VertexArrayGo(textureId, "Background");
	sf::Vector2f startPos = { 0,0 };

	sf::VertexArray& vertexArray = background->GetVertexArray();
	background->SetPrimitiveType(sf::Quads);
	background->ReSize(size.x * size.y * 4);

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
	for (int i = 0; i < size.y; ++i)
	{
		for (int j = 0; j < size.x; ++j)
		{
			int tileIndex = size.x * i + j;
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
