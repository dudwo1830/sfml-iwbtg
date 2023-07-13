#pragma once
#include "GameObject.h"

class TextGo : public GameObject
{
protected:
	std::string fontId;

public:
	sf::Text text;

	TextGo(const std::string& fontId, const std::string& name);
	virtual ~TextGo();

	virtual void SetPosition(float x, float y);
	virtual void SetPosition(const sf::Vector2f& p);

	virtual void SetOrigin(Origins origin);
	virtual void SetOrigin(float x, float y);

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float deltaTime) override;
	virtual void Draw(sf::RenderWindow& window) override;
};

