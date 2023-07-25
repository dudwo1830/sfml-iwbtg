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

void Spike::Update(float deltaTime)
{
    ConvexShapeGo::Update(deltaTime);
}
