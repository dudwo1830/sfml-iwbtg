#pragma once
#include "SpriteGo.h"
class MoreJump : public SpriteGo
{
protected:

	MoreJump(const MoreJump& other) = delete;
	bool operator==(const MoreJump& other) const = delete;
public:
	MoreJump(const std::string& textureId = "", const std::string& name = "");
	virtual ~MoreJump() override;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Update(float deltaTime) override;
	virtual void Draw(sf::RenderWindow& window) override;
};

