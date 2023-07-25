#pragma once
#include "ConvexShapeGo.h"
class Spike : public ConvexShapeGo
{
protected:

	Spike(const Spike& other) = delete;
	bool operator==(const Spike& other) const = delete;
public:
	Spike(const std::string& textureId = "", const std::string& n = "", int pointCount = 3);
	virtual ~Spike();

	const sf::Vector2f& GetPosition() const { return position; }

	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float deltaTime) override;
};

