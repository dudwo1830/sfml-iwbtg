#include "stdafx.h"
#include "VertexArrayGo.h"
#include "ResourceMgr.h"

VertexArrayGo::VertexArrayGo(const std::string& textureId, const std::string& name)
	:GameObject(name), textureId(textureId), texture(nullptr)
{
	outline.setPrimitiveType(sf::Lines);
}

VertexArrayGo::~VertexArrayGo()
{
}

void VertexArrayGo::SetPosition(float x, float y)
{
	SetPosition({x, y});
}

void VertexArrayGo::SetPosition(const sf::Vector2f& p)
{
	sf::Vector2f diff = p - position;
	position = p;
	for (int i = 0; i < vertexArray.getVertexCount(); i++)
	{
		vertexArray[i].position += diff;
	}
}

void VertexArrayGo::SetOrigin(Origins origin)
{
	GameObject::SetOrigin(origin);
	if (origin == Origins::CUSTOM)
	{
		return;
	}

	sf::Vector2f prevOrigin = originPosition;
	sf::FloatRect bounds = vertexArray.getBounds();
	originPosition.x = bounds.width * ((int)origin % 3) * 0.5f;
	originPosition.y = bounds.height * ((int)origin / 3) * 0.5f;
	sf::Vector2f diff = prevOrigin - originPosition;

	for (int i = 0; i < vertexArray.getVertexCount(); i++)
	{
		vertexArray[i].position += diff;
	}
}

void VertexArrayGo::SetOrigin(float x, float y)
{
	GameObject::SetOrigin(x, y);

	sf::Vector2f prevOrigin = originPosition;
	sf::FloatRect bounds = vertexArray.getBounds();
	originPosition.x = x;
	originPosition.y = y;
	sf::Vector2f diff = prevOrigin - originPosition;

	for (int i = 0; i < vertexArray.getVertexCount(); i++)
	{
		vertexArray[i].position += diff;
	}
}

void VertexArrayGo::Init()
{
}

void VertexArrayGo::Release()
{
}

void VertexArrayGo::Reset()
{
	texture = RESOURCE_MGR.GetTexture(textureId);
}

void VertexArrayGo::Update(float deltaTime)
{
}

void VertexArrayGo::Draw(sf::RenderWindow& window)
{
	window.draw(vertexArray, texture);
	if (outlineActive)
	{
		window.draw(outline);
	}
}

sf::VertexArray& VertexArrayGo::GetVertexArray()
{
	return vertexArray;
}

sf::VertexArray& VertexArrayGo::GetOutline()
{
	return outline;
}

sf::Vector2u VertexArrayGo::GetTextureSize()
{
	return texture->getSize();
}

void VertexArrayGo::SetPrimitiveType(sf::PrimitiveType type)
{
	vertexArray.setPrimitiveType(type);
}

void VertexArrayGo::ReSize(int size)
{
	vertexArray.resize(size);
}

sf::FloatRect VertexArrayGo::GetBounds()
{
	return vertexArray.getBounds();
}

const std::string& VertexArrayGo::GetTextureId()
{
	return textureId;
}

void VertexArrayGo::SetTextureId(const std::string& textureId)
{
	this->textureId = textureId;
}

void VertexArrayGo::SwitchOutline(bool trigger)
{
	outlineActive = trigger;
}

