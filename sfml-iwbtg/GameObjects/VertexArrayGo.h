#pragma once
#include "GameObject.h"
class VertexArrayGo : public GameObject
{
protected:
	std::string textureId;
	sf::Texture* texture;
	sf::Vector2f originPosition;

public:
	sf::VertexArray vertexArray;

	VertexArrayGo(const std::string& textureId, const std::string& name = "");
	virtual ~VertexArrayGo() override;

	virtual void SetPosition(float x, float y);
	virtual void SetPosition(const sf::Vector2f& p);

	virtual void SetOrigin(Origins origin);
	virtual void SetOrigin(float x, float y);

	// GameObject을(를) 통해 상속됨
	virtual void Init();
	virtual void Release();

	virtual void Reset();

	virtual void Update(float deltaTime);
	virtual void Draw(sf::RenderWindow& window);
};

