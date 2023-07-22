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
	bool isHide = false;

	std::function<void()> collideEvent;
public:
	Obstacle(const std::string& textureId = "", const std::string& name = "");
	virtual ~Obstacle() override;

	void SetType(Type type) { this->type = type; }

	virtual void SetCollideEvent(std::function<void()> obsEvent);
	void CollideCheck(const sf::FloatRect& bounds);

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;
};

