#include "stdafx.h"
#include "SpriteGo.h"
#include "ResourceMgr.h"

SpriteGo::SpriteGo(const std::string& textureId, const std::string& name)
	:GameObject(name), textureId(textureId)
{
}

SpriteGo::~SpriteGo()
{
}

void SpriteGo::SetPosition(float x, float y)
{
	position.x = x;
	position.y = y;
	sprite.setPosition(position);
}

void SpriteGo::SetPosition(const sf::Vector2f& p)
{
	position = p;
	sprite.setPosition(position);
}

void SpriteGo::SetOrigin(float x, float y)
{
	GameObject::SetOrigin(x, y);
	sprite.setOrigin(x, y);
}

sf::Sprite& SpriteGo::GetSprite()
{
	return sprite;
}

const std::string& SpriteGo::GetTextureId()
{
	return textureId;
}

void SpriteGo::SetTextureId(const std::string& id)
{
	textureId = id;
}

void SpriteGo::SetOrigin(Origins origin)
{
	GameObject::SetOrigin(origin);
	if (this->origin != Origins::CUSTOM)
	{
		Utils::SetOrigin(sprite, origin);
	}
}

void SpriteGo::Init()
{
}

void SpriteGo::Release()
{
}

void SpriteGo::Reset()
{
	sf::Texture* tex = RESOURCE_MGR.GetTexture(textureId);
	if (tex != nullptr)
	{
		sprite.setTexture(*tex);
	}
	SetOrigin(origin);
}

void SpriteGo::Update(float deltaTime)
{
}

void SpriteGo::Draw(sf::RenderWindow& window)
{	
	window.draw(sprite);
}
