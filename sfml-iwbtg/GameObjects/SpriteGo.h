#pragma once
#include "GameObject.h"

class SpriteGo : public GameObject
{
protected:
	sf::Sprite sprite;
	std::string textureId;

	SpriteGo(const SpriteGo& other) = delete;
	bool operator==(const SpriteGo& other) const = delete;
public:
	SpriteGo(const std::string& textureId = "", const std::string & name = "");
	virtual ~SpriteGo();

	virtual void SetPosition(float x, float y);
	virtual void SetPosition(const sf::Vector2f& p);

	virtual void SetOrigin(Origins origin);
	virtual void SetOrigin(float x, float y);

	virtual sf::Sprite& GetSprite();
	virtual const sf::FloatRect& GetBounds();
	virtual const std::string& GetTextureId();
	virtual void SetTextureId(const std::string& id);

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float deltaTime) override;
	virtual void Draw(sf::RenderWindow& window) override;
};

