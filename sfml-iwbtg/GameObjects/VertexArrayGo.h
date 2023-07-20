#pragma once
#include "GameObject.h"
class VertexArrayGo : public GameObject
{
protected:
	std::string textureId;
	sf::Texture* texture;
	sf::Vector2f originPosition;
	sf::VertexArray vertexArray;

	sf::VertexArray outline;
	bool outlineActive = false;

	VertexArrayGo(const VertexArrayGo& other) = delete;
	bool operator==(const VertexArrayGo& other) const = delete;
public:
	VertexArrayGo(const std::string& textureId, const std::string& name = "");
	virtual ~VertexArrayGo() override;

	virtual void SetPosition(float x, float y);
	virtual void SetPosition(const sf::Vector2f& p);

	virtual void SetOrigin(Origins origin);
	virtual void SetOrigin(float x, float y);

	virtual void Init();
	virtual void Release();
	virtual void Reset();
	virtual void Update(float deltaTime);
	virtual void Draw(sf::RenderWindow& window);

	sf::VertexArray& GetVertexArray();
	sf::VertexArray& GetOutline();
	sf::Vector2u GetTextureSize();
	void SetPrimitiveType(sf::PrimitiveType type);
	void ReSize(int size);

	sf::FloatRect GetBounds();
	const std::string& GetTextureId();
	void SetTextureId(const std::string& textureId);
	
	void SwitchOutline(bool trigger);
};

