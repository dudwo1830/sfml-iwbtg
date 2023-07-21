#pragma once
#include "SpriteGo.h"
class Obstacle : public SpriteGo
{
public:
	enum class Type
	{
		None,
		Item,
		Save,
		WallClimb,
		Trap,
	};
protected:
	Type type = Type::None;
public:
	Obstacle(const std::string& textureId = "", const std::string& name = "");
	virtual ~Obstacle() override;

	void SetType(Type type) { this->type = type; }

	virtual void Init()override;
	virtual void Reset()override;
	virtual void Release() override;

	virtual void Update(float dt)override;
	virtual void Draw(sf::RenderWindow& window)override;
};

