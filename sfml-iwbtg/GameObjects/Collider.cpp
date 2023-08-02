#include "stdafx.h"
#include "Collider.h"

Collider::Collider()
{
}

bool Collider::CheckCollision(const Collider& other) const 
{
    return GetBounds().intersects(other.GetBounds());
}

void Collider::ResolveCollision(Collider& other)
{
    sf::Vector2f correction = CalculateCorrection(other);
    SetPosition(GetPosition() + correction);
}

sf::Vector2f Collider::CalculateCorrection(const Collider& other) const 
{
    sf::Vector2f myPosition = GetPosition();
    sf::Vector2f otherPosition = other.GetPosition();

    sf::Vector2f myHalfSize = GetSize() / 2.0f;
    sf::Vector2f otherHalfSize = other.GetSize() / 2.0f;

    float deltaX = (myPosition.x + myHalfSize.x) - (otherPosition.x + otherHalfSize.x);
    float deltaY = (myPosition.y + myHalfSize.y) - (otherPosition.y + otherHalfSize.y);
    float intersectX = abs(deltaX) - (myHalfSize.x + otherHalfSize.x);
    float intersectY = abs(deltaY) - (myHalfSize.y + otherHalfSize.y);

    sf::Vector2f correction(0.0f, 0.0f);

    // X 축 보정
    if (intersectX < 0.0f) {
        if (abs(intersectX) < abs(intersectY)) {
            correction.x = -intersectX * (deltaX < 0.0f ? 1.0f : -1.0f);
        }
    }

    // Y 축 보정
    if (intersectY < 0.0f) {
        if (abs(intersectY) < abs(intersectX)) {
            correction.y = -intersectY * (deltaY < 0.0f ? 1.0f : -1.0f);
        }
    }

    return correction;
}