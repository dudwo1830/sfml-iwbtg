#pragma once
#include "SpriteGo.h"
#include "Scene.h"
#include "AnimationController.h"

class Save : public SpriteGo
{
protected:
	//여유가 있으면 적용해보자..
	AnimationController animation;

	SceneId sceneid = SceneId::None;
	sf::Vector2f restartPos;


	Save(const Save& other) = delete;
	bool operator==(const Save& other) const = delete;

public:
	//test
	sf::RectangleShape shape;

	Save(const std::string& textureId = "", const std::string& name = "");
	virtual ~Save();

	const sf::Vector2f& GetRestartPos();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Update(float deltaTime) override;
	virtual void Draw(sf::RenderWindow& window) override;
};

