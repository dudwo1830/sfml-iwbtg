#pragma once
class Collider
{
private:
    sf::RectangleShape body;

public:
    Collider(sf::RectangleShape& body);
    ~Collider();

    bool CheckCollision(Collider& target, float push);

    void Move(float dx, float dy) { body.move(dx, dy); }
    sf::Vector2f GetPosition() { return body.getPosition(); }
    sf::Vector2f GetHalfSize() { return body.getSize() / 2.f; }
};

