#include "stdafx.h"
#include "Scene.h"
#include "GameObject.h"
#include "ResourceMgr.h"
#include "Framework.h"
#include "rapidcsv.h"
#include "Obstacle.h"
#include "SaveLoadMgr.h"
#include "SceneMgr.h"

Scene::Scene(SceneId id) : sceneId(id), window(FRAMEWORK.GetWindow())
{
}

Scene::~Scene()
{
}

GameObject* Scene::FindGo(const std::string& name)
{
	//auto compare = [name](GameObject* go) { return go->GetName() == name; };
	//auto it = std::find_if(gameObjects.begin(), gameObjects.end(), compare);
	//if (it == gameObjects.end())
	//	return nullptr;
	//return *it;

	for (auto go : gameObjects)
	{
		if (go->GetName() == name)
		{
			return go;
		}
	}
	return nullptr;
}

void Scene::FindGos(std::list<GameObject*>& list, const std::string& name)
{
	//list.clear();
	for (auto go : gameObjects)
	{
		if (go->GetName() == name)
		{
			list.push_back(go);
		}
	}
}

bool Scene::Exist(GameObject* go)
{
	return std::find(gameObjects.begin(), gameObjects.end(), go) != gameObjects.end();
}

GameObject* Scene::AddGo(GameObject* go)
{
	if (!Exist(go))
	{
		gameObjects.push_back(go);
	}
	return go;
}

void Scene::RemoveGo(GameObject* go)
{
	removeGameObjects.push_back(go);
}

void Scene::SortGos()
{
	gameObjects.sort([](GameObject* lhs, GameObject* rhs) {
		if (lhs->sortLayer != rhs->sortLayer)
			return lhs->sortLayer < rhs->sortLayer;
		return lhs->sortOrder < rhs->sortOrder;
		});
}

sf::Vector2f Scene::ScreenToWorldPos(sf::Vector2f screenPos)
{
	return window.mapPixelToCoords((sf::Vector2i)screenPos, worldView);
}

sf::Vector2f Scene::ScreenToUiPos(sf::Vector2f screenPos)
{
	return window.mapPixelToCoords((sf::Vector2i)screenPos, uiView);
}

sf::Vector2f Scene::WorldPosToScreen(sf::Vector2f worldPos)
{
	return (sf::Vector2f)window.mapCoordsToPixel(worldPos, worldView);
}

sf::Vector2f Scene::UiPosPosToScreen(sf::Vector2f uiPos)
{
	return (sf::Vector2f)window.mapCoordsToPixel(uiPos, uiView);
}

void Scene::Enter()
{
	RESOURCE_MGR.LoadFromCSV(resourceListPath);

	for (auto go : gameObjects)
	{
		go->Reset();
	}
}

void Scene::Exit()
{
	for (auto go : removeGameObjects)
	{
		gameObjects.remove(go);
	}
	removeGameObjects.clear();

	RESOURCE_MGR.UnLoadAll();
}

void Scene::Update(float dt)
{
	for (auto go : gameObjects)
	{
		if (go->GetActive())
		{
			go->Update(dt);
		}
	}

	for (auto go : removeGameObjects)
	{
		gameObjects.remove(go);
	}
	removeGameObjects.clear();
}

void Scene::Draw(sf::RenderWindow& window)
{
	// layer 100 บฮลอดย ui Layer

	SortGos();

	window.setView(worldView);

	for (auto go : gameObjects)
	{
		if (go->sortLayer >= 100)
			continue;

		if (go->GetActive())
		{
			go->Draw(window);
		}
	}

	window.setView(uiView);

	for (auto go : gameObjects)
	{
		if (go->sortLayer < 100)
			continue;

		if (go->GetActive())
		{
			go->Draw(window);
		}
	}
}

void Scene::SaveData()
{
	std::map<std::string, std::string> dataMap;
	dataMap["SceneId"] = std::to_string((int)sceneId);
	dataMap["PositionX"] = std::to_string(Variables::CheckPoint.x);
	dataMap["PositionY"] = std::to_string(Variables::CheckPoint.y);
	dataMap["DeathCount"] = std::to_string(Variables::DeathCount);
	dataMap["FlipX"] = std::to_string(Variables::PlayerFlip);
	SAVELOAD_MGR.SaveGame(SAVELOAD_MGR.GetCurrentFileName(), dataMap);
}

void Scene::LoadData()
{
	std::map<std::string, std::string> dataMap;
	SAVELOAD_MGR.LoadGame(SAVELOAD_MGR.GetCurrentFileName(), dataMap);

	SceneId sceneIdData = (SceneId)stoi(dataMap.find("SceneId")->second);
	Variables::CheckPoint.x = stof(dataMap.find("PositionX")->second);
	Variables::CheckPoint.y = stof(dataMap.find("PositionY")->second);
	Variables::PlayerFlip = stoi(dataMap.find("FlipX")->second);
	Variables::DeathCount = stoi(dataMap.find("DeathCount")->second);

	if (sceneIdData != sceneId)
	{
		SCENE_MGR.ChangeScene(sceneIdData);
	}
	else
	{
		Scene* scene = SCENE_MGR.GetCurrentScene();
		scene->Enter();
	}
}