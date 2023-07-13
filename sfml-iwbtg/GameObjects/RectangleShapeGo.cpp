#include "stdafx.h"
#include "RectangleShapeGo.h"
#include "Utils.h"
#include "InputMgr.h"
#include "Framework.h"

RectangleShapeGo::RectangleShapeGo(const std::string& textureId, const std::string& n)
    :GameObject(n)
{
}

RectangleShapeGo::~RectangleShapeGo()
{
}

void RectangleShapeGo::SetPosition(float x, float y)
{
    position.x = x;
    position.y = y;
    shape.setPosition(x, y);
}

void RectangleShapeGo::SetPosition(const sf::Vector2f& p)
{
    position = p;
    shape.setPosition(position);
}

void RectangleShapeGo::SetOrigin(Origins origin)
{
    GameObject::SetOrigin(origin);
    if (this->origin != Origins::CUSTOM)
    {
        Utils::SetOrigin(shape, origin);
    }
}

void RectangleShapeGo::SetOrigin(float x, float y)
{
    GameObject::SetOrigin(x, y);
    shape.setOrigin(x, y);
}

void RectangleShapeGo::Init()
{

}

void RectangleShapeGo::Release()
{
}

void RectangleShapeGo::Reset()
{
}

const sf::Vector2f& RectangleShapeGo::GetPosition() const
{
    return position;
}

sf::FloatRect RectangleShapeGo::GetBounds() const
{
    return shape.getGlobalBounds();
}

const sf::RectangleShape& RectangleShapeGo::GetShape()
{
    return shape;
}

void RectangleShapeGo::Update(float dt)
{

}

void RectangleShapeGo::Draw(sf::RenderWindow& window)
{
    window.draw(shape);
}
