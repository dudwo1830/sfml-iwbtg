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
    //sf::Transform trans;
    //sf::Vector2f centerPos = position;
    //centerPos.x += shape.getTexture()->getSize().x / 2.f;
    //centerPos.y += shape.getTexture()->getSize().y / 2.f;
    //trans.rotate(angle, centerPos);
    window.draw(shape);
}

float ConvexShapeGo::dotProduct(const sf::Vector2f& lhs, const sf::Vector2f& rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

void ConvexShapeGo::getMinMax(const std::vector<sf::Vector2f>& shape, const sf::Vector2f& axis, float& min, float& max)
{
    min = dotProduct(shape[0], axis);
    max = min;

    for (const auto& point : shape) {
        float projection = dotProduct(point, axis);
        min = std::min(min, projection);
        max = std::max(max, projection);
    }
}

bool ConvexShapeGo::isColliding(const sf::RectangleShape& rect)
{
    std::vector<sf::Vector2f> axes;

    // ConvexShape의 면에 대한 정규 벡터 계산
    for (int i = 0; i < shape.getPointCount(); i++) {
        sf::Vector2f point1 = shape.getTransform().transformPoint(shape.getPoint(i));
        sf::Vector2f point2 = shape.getTransform().transformPoint(shape.getPoint((i + 1) % shape.getPointCount()));
        sf::Vector2f edge = point1 - point2;
        axes.push_back({ edge.y, -edge.x });
    }

    // RectangleShape의 면에 대한 정규 벡터 계산
    for (int i = 0; i < 4; i++) {
        sf::Vector2f point1 = rect.getTransform().transformPoint(rect.getPoint(i));
        sf::Vector2f point2 = rect.getTransform().transformPoint(rect.getPoint((i + 1) % 4));
        sf::Vector2f edge = point1 - point2;
        axes.push_back({ edge.y, -edge.x });
    }

    // ConvexShape의 모든 꼭짓점을 구함
    std::vector<sf::Vector2f> shapePoints;
    for (int i = 0; i < shape.getPointCount(); i++) {
        shapePoints.push_back(shape.getTransform().transformPoint(shape.getPoint(i)));
    }

    // RectangleShape의 모든 꼭짓점을 구함
    std::vector<sf::Vector2f> rectPoints;
    for (int i = 0; i < 4; i++) {
        rectPoints.push_back(rect.getTransform().transformPoint(rect.getPoint(i)));
    }

    // 각 축에 대해 두 도형을 투영하고 겹치는 범위가 있는지 검사
    for (const auto& axis : axes) {
        float minConvex, maxConvex, minRect, maxRect;
        getMinMax(shapePoints, axis, minConvex, maxConvex);
        getMinMax(rectPoints, axis, minRect, maxRect);
        if (maxConvex < minRect || maxRect < minConvex) {
            return false;
        }
    }

    return true;

}
