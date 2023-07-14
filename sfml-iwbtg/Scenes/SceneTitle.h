#pragma once
#include "Scene.h"

class Player;
class TileMap;

class SceneTitle : public Scene
{
protected:
	TileMap* tileMap = nullptr;
	Player* player = nullptr;

public:
	SceneTitle();
	virtual ~SceneTitle() override;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
};

