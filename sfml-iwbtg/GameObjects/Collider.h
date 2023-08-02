#pragma once
#include "RectangleShapeGo.h"
class Collider : public RectangleShapeGo {

protected:
    sf::Vector2f CalculateCorrection(const Collider& other) const;

public:
    Collider();
    bool CheckCollision(const Collider& other) const;
    void ResolveCollision(Collider& other);

};