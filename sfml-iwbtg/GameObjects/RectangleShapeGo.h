#pragma once
#include "GameObject.h"

class Player;

class RectangleShapeGo : public GameObject
{
protected:
	sf::RectangleShape shape;
	sf::Vector2f position;
	sf::Vector2f direction;
	bool isPass;

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

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
};