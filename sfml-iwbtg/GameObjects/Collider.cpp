#include "stdafx.h"
#include "Collider.h"

Collider::Collider(sf::RectangleShape& body)
    :body(body)
{
}

Collider::~Collider()
{
}

bool Collider::CheckCollision(Collider& target, float push)
{
    sf::Vector2f targetPosition = target.GetPosition();
    sf::Vector2f targetHalfSize = target.GetHalfSize();
    sf::Vector2f thisPosition = GetPosition();
    sf::Vector2f thisHalfSize = GetHalfSize();

    float deltaX = targetPosition.x - thisPosition.x;
    float deltaY = targetPosition.y - thisPosition.y;
    float intersectX = abs(deltaX) - (targetHalfSize.x + thisHalfSize.x);
    float intersectY = abs(deltaY) - (targetHalfSize.y + thisHalfSize.y);
   
    if (intersectX > 0.f && intersectY > 0.f)
    {
        if (intersectX > intersectY)
        {
            if (deltaX > 0.f)
            {
                Move(intersectX * (1.f - push), 0.f);
                target.Move(-intersectX * push, 0.f);
            }
            else
            {
                Move(-intersectX * (1.f - push), 0.f);
                target.Move(intersectX * push, 0.f);
            }
        }
        else
        {
            if (deltaY > 0.f)
            {
                Move(0.f, intersectY * (1.f - push));
                target.Move(0.f, -intersectY * push);
            }
            else
            {
                Move(0.f, -intersectY * (1.f - push));
                target.Move(0.f, intersectY * push);
            }
        }
    }
    else // 대각선 방향에서는 충돌이 없는 경우
    {
        if (intersectX > 0.f)
        {
            if (deltaX > 0.f)
            {
                Move(intersectX * (1.f - push), 0.f);
                target.Move(-intersectX * push, 0.f);
            }
            else
            {
                Move(-intersectX * (1.f - push), 0.f);
                target.Move(intersectX * push, 0.f);
            }
        }
        else if (intersectY > 0.f)
        {
            if (deltaY > 0.f)
            {
                Move(0.f, intersectY * (1.f - push));
                target.Move(0.f, -intersectY * push);
            }
            else
            {
                Move(0.f, -intersectY * (1.f - push));
                target.Move(0.f, intersectY * push);
            }
        }
    }

    return false;
}
