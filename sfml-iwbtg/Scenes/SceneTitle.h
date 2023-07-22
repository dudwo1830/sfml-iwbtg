#pragma once
#include "Scene.h"
#include "VertexArrayGo.h"

class Player;
class TileMap;
class SpriteGo;
class Obstacle;

class SceneTitle : public Scene
{
protected:
	TileMap* tileMap = nullptr;
	std::list<Obstacle*> obsList;

	Player* player = nullptr;
	SpriteGo* gameOver = nullptr;

public:
	SceneTitle();
	virtual ~SceneTitle() override;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	VertexArrayGo* CreateBackground(const sf::Vector2f& tileMatrix, const sf::Vector2f& tileSize, const sf::Vector2f& texSize = {0.f, 0.f}, const std::string& textureId = "");

	bool LoadObs(const std::string& path, sf::Vector2f tileSize = { 0.f, 0.f });
	void SetObsEvent(const std::string& id, std::function<void()> event);
};

