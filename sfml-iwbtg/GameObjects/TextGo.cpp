#include "stdafx.h"
#include "TextGo.h"
#include "ResourceMgr.h"

TextGo::TextGo(const std::string& fontId, const std::string& str)
	:GameObject(str), fontId(fontId)
{

}

TextGo::~TextGo()
{
}

void TextGo::SetPosition(float x, float y)
{
	position.x = x;
	position.y = y;
	text.setPosition(position);
}

void TextGo::SetPosition(const sf::Vector2f& p)
{
	position = p;
	text.setPosition(position);
}

void TextGo::SetOrigin(float x, float y)
{
	GameObject::SetOrigin(x, y);
	text.setOrigin(x, y);
}

void TextGo::SetOrigin(Origins origin)
{
	GameObject::SetOrigin(origin);
	if (this->origin != Origins::CUSTOM)
	{
		Utils::SetOrigin(text, origin);
	}
}

void TextGo::Init()
{
}

void TextGo::Release()
{
}

void TextGo::Reset()
{
	sf::Font* font = RESOURCE_MGR.GetFont(fontId);
	if (font != nullptr)
	{
		text.setFont(*font);
	}
	SetOrigin(origin);
}

void TextGo::Update(float deltaTime)
{
}

void TextGo::Draw(sf::RenderWindow& window)
{
	window.draw(text);
}
