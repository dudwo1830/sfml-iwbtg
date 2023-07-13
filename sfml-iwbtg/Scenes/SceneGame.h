#pragma once
#include "Scene.h"
#include "ObjectPool.h"

class SpriteEffect;
class VertexArrayGo;

class SceneGame : public Scene
{
protected:
	sf::FloatRect wallBounds;

	sf::Cursor cursor;
	bool isGameOver;
public:
	SceneGame();
	virtual ~SceneGame() override;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
	
	VertexArrayGo* CreateBackground(sf::Vector2i size, sf::Vector2f tileSize, sf::Vector2f texSize, std::string textureId);

	template<typename T>
	void ClearObjectPool(ObjectPool<T>& pool);
};

template<typename T>
inline void SceneGame::ClearObjectPool(ObjectPool<T>& pool)
{
	for (auto obj : pool.GetUseList())
	{
		RemoveGo(obj);
	}
	pool.Clear();
}
