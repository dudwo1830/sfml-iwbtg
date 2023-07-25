#pragma once
#include "GameObject.h"

class RectangleShapeGo : public GameObject
{
protected:
	std::string textureId;
	sf::RectangleShape shape;
	sf::Vector2f direction;

	RectangleShapeGo(const RectangleShapeGo& other) = delete;
	bool operator==(const RectangleShapeGo& other) const = delete;
public:
	RectangleShapeGo(const std::string& textureId = "", const std::string& n = "");
	virtual ~RectangleShapeGo();

	virtual void SetPosition(float x, float y);
	virtual void SetPosition(const sf::Vector2f& p);

	virtual void SetOrigin(Origins origin);
	virtual void SetOrigin(float x, float y);

	void SetSize(sf::Vector2f size) { shape.setSize(size); }

	const sf::Vector2f& GetPosition() const;
	sf::FloatRect GetBounds() const;
	const sf::RectangleShape& GetShape();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float deltaTime) override;
	virtual void Draw(sf::RenderWindow& window) override;
};