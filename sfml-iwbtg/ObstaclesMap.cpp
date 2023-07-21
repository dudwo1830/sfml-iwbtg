#include "stdafx.h"
#include "ObstaclesMap.h"
#include "rapidcsv.h"
#include "Obstacle.h"
#include "SceneMgr.h"

ObstaclesMap::ObstaclesMap(const std::string& name)
    :GameObject(name)
{
}

ObstaclesMap::~ObstaclesMap()
{
}

bool ObstaclesMap::Load(const std::string& filePath)
{
    rapidcsv::Document map(filePath, rapidcsv::LabelParams(-1, -1));
    for (int i = 1; i < map.GetRowCount(); i++)
    {
        Obstacle::Type type = (Obstacle::Type)map.GetCell<int>(0, i);
        std::string id = map.GetCell<std::string>(1, i);
        std::string textureId = map.GetCell<std::string>(2, i);
        bool useTileSize = map.GetCell<int>(3, i);
        float leftValue = map.GetCell<float>(4, i);
        float topValue = map.GetCell<float>(5, i);
        int sort = i;
        if (map.GetCell<std::string>(6, i) != "")
        {
            sort = std::stoi(map.GetCell<std::string>(6, i));
        }

        sf::Vector2f position = { leftValue, topValue };
        if (useTileSize)
        {
            position.x *= tileSize.x;
            position.y *= tileSize.y;
        }

        Obstacle* obs = (Obstacle*)SCENE_MGR.GetCurrentScene()->AddGo(new Obstacle(textureId, id));
        obs->SetPosition(position);
        obs->sortLayer = sort;
    }
    return true;
}

void ObstaclesMap::Init()
{
}

void ObstaclesMap::Reset()
{
}

void ObstaclesMap::Release()
{
}

void ObstaclesMap::Update(float dt)
{
}

void ObstaclesMap::Draw(sf::RenderWindow& window)
{
}
