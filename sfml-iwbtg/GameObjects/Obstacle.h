#pragma once
#include "SpriteGo.h"
#include "Collider.h"

class Obstacle : public SpriteGo
{
public:
	enum class Type
	{
		None,
		Item,
		Save,
		WallClimb,
		Block,
		Trap,
		Clear,
	};
protected:
	Type type = Type::None;
	bool defaultHide = false;
	bool isHide = false;

	std::function<void()> collideEvent;

	float hideTime = 0.f;
	float timer = 0.f;
public:

	Obstacle(const std::string& textureId = "", const std::string& name = "");
	virtual ~Obstacle() override;

	void SetType(Type& type) { this->type = type; }
	Type GetType() { return type; }
	void SetDefaultHide(bool hide) { this->defaultHide = hide; }
	void SetHide(bool hide) { this->isHide = hide; }
	void SetHideTime(float time) { this->hideTime = time; timer = 0.f; }

	void SetCollideEvent(std::function<void()> obsEvent);
	void CollideCheck(const sf::FloatRect& bounds);
	
	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Update(float deltaTime) override;
	virtual void Draw(sf::RenderWindow& window) override;
};

