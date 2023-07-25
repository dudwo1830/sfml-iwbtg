#pragma once
#include "GameObject.h"
class ConvexShapeGo : public GameObject
{
protected:
	std::string textureId;
	sf::ConvexShape shape;
	sf::Vector2f position;
	sf::Vector2f direction;
	float angle;
	
	ConvexShapeGo(const ConvexShapeGo& other) = delete;
	bool operator==(const ConvexShapeGo& other) const = delete;
public:
	ConvexShapeGo(const std::string& textureId = "", const std::string& n = "", int pointCount = 3);
	virtual ~ConvexShapeGo();

	virtual void SetPosition(float x, float y);
	virtual void SetPosition(const sf::Vector2f& p);

	virtual void SetOrigin(Origins origin);
	virtual void SetOrigin(float x, float y);

	void SetPoint(int index, sf::Vector2f point);
	void SetRotaition(float angle) { shape.setRotation(angle); }
	void SetAngle(float angle) { this->angle = angle; };

	const sf::Vector2f& GetPosition() const { return position; }
	const sf::FloatRect GetBounds() const { return shape.getGlobalBounds(); }

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	//Collision
	float dotProduct(const sf::Vector2f& lhs, const sf::Vector2f& rhs);
	void getMinMax(const std::vector<sf::Vector2f>& shape, const sf::Vector2f& axis, float& min, float& max);
	bool isColliding(const sf::RectangleShape& rect);
};

