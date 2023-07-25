#include "stdafx.h"
#include "Spike.h"

Spike::Spike(const std::string& textureId, const std::string& n, int pointCount)
    :ConvexShapeGo(textureId, n, pointCount)
{
}

Spike::~Spike()
{
}

void Spike::Release()
{
}

void Spike::Reset()
{
    ConvexShapeGo::Reset();
}

bool Spike::CollideCheck(const sf::FloatRect& bounds)
{
    return GetBounds().intersects(bounds);
}

void Spike::Update(float deltaTime)
{
    ConvexShapeGo::Update(deltaTime);
}
