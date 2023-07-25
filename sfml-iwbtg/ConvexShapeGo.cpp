#include "stdafx.h"
#include "ConvexShapeGo.h"
#include "ResourceMgr.h"

ConvexShapeGo::ConvexShapeGo(const std::string& textureId, const std::string& n, int pointCount)
    :GameObject(n), textureId(textureId)
{
    shape.setPointCount(pointCount);
}

ConvexShapeGo::~ConvexShapeGo()
{
}

void ConvexShapeGo::SetPosition(float x, float y)
{
    position.x = x;
    position.y = y;
    shape.setPosition(x, y);
}

void ConvexShapeGo::SetPosition(const sf::Vector2f& p)
{
    position = p;
    shape.setPosition(position);
}

void ConvexShapeGo::SetOrigin(Origins origin)
{
    GameObject::SetOrigin(origin);
    if (this->origin != Origins::CUSTOM)
    {
        Utils::SetOrigin(shape, origin);
    }
}

void ConvexShapeGo::SetOrigin(float x, float y)
{
    GameObject::SetOrigin(x, y);
    shape.setOrigin(x, y);
}

void ConvexShapeGo::SetPoint(int index, sf::Vector2f point)
{
    shape.setPoint(index, point);
}

void ConvexShapeGo::Init()
{
}

void ConvexShapeGo::Release()
{
}

void ConvexShapeGo::Reset()
{
    sf::Texture* tex = RESOURCE_MGR.GetTexture(textureId);
    if (tex != nullptr)
    {
        shape.setTexture(tex);
    }
    //shape.setOutlineColor(sf::Color::Green);
    //shape.setOutlineThickness(1.f);
    SetOrigin(origin);
}

void ConvexShapeGo::Update(float dt)
{
}

void ConvexShapeGo::Draw(sf::RenderWindow& window)
{
    sf::Transform trans;
    sf::Vector2f centerPos = position;
    centerPos.x += shape.getTexture()->getSize().x / 2.f;
    centerPos.y += shape.getTexture()->getSize().y / 2.f;
    trans.rotate(angle, centerPos);
    window.draw(shape, trans);
}
