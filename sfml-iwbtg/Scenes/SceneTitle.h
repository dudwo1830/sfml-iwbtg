#pragma once
#include "Scene.h"
#include "VertexArrayGo.h"

class Player;
class TileMap;
class SpriteGo;
class Save;

class SceneTitle : public Scene
{
protected:
	TileMap* tileMap = nullptr;
	Player* player = nullptr;
	SpriteGo* gameOver = nullptr;

	std::vector<Save*> saveList;
public:
	SceneTitle();
	virtual ~SceneTitle() override;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	VertexArrayGo* CreateBackground(sf::Vector2f size, sf::Vector2f tileSize, sf::Vector2f texSize, std::string textureId);
};

