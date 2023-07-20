#pragma once
#include "Utils.h"

class GameObject
{
protected:
	std::string name;
	sf::Vector2f position;
	bool isActive = true;
	Origins origin = Origins::TL;

public:
	sf::RectangleShape outline;
	int sortLayer = 0;
	int sortOrder = 0;

	GameObject(const std::string& name = "");
	virtual ~GameObject();

	bool GetActive() const;
	void SetActive(bool active);

	std::string GetName();
	virtual void SetName(const std::string& n);

	sf::Vector2f GetPosition();
	virtual void SetPosition(float x, float y);
	virtual void SetPosition(const sf::Vector2f& p);

	virtual void SetOrigin(Origins origin);
	virtual void SetOrigin(float x, float y);

	virtual void Init() = 0; //생성자 역할
	virtual void Release() {}; //소멸자 역할

	virtual void Reset() = 0; //초기화

	virtual void Update(float deltaTime) = 0;
	virtual void Draw(sf::RenderWindow& window) = 0;

	void SwitchOutline(bool trigger);
	void SetOutlineThickness(float thickness);
	void SetOutlineColor(sf::Color color);
};

