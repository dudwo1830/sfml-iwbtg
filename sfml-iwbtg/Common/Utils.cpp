#include "stdafx.h"
#include "Utils.h"
#include <sstream>
std::random_device Utils::rd;
std::mt19937 Utils::gen(Utils::rd());

int Utils::RandomRange(int min, int maxExclude)
{
    std::uniform_int_distribution<> dist(min, maxExclude - 1);
    return dist(gen);
}

float Utils::RandomRange(float min, float max)
{
    std::uniform_real_distribution<> dist(min, max);
    return (float)dist(gen);
}

sf::Vector2f Utils::RandomOnCircle(float radius)
{
    sf::Vector2f vec(RandomRange(-1.0f, 1.0f), RandomRange(-1.0f, 1.0f));
    vec = Normalize(vec) * radius;
    return vec;
}

sf::Vector2f Utils::RandomInCircle(float radius)
{
    return RandomOnCircle(radius) * RandomValue();
}

float Utils::RandomValue()
{
    return RandomRange(0.0f, 1.0f);
}

void Utils::SetOrigin(sf::Sprite& sprite, Origins origin)
{
    SetOrigin(sprite, origin, sprite.getLocalBounds());
}

void Utils::SetOrigin(sf::Text& text, Origins origin)
{
    SetOrigin(text, origin, text.getLocalBounds());
}

void Utils::SetOrigin(sf::Shape& shape, Origins origin)
{
    SetOrigin(shape, origin, shape.getLocalBounds());
}

void Utils::SetOrigin(sf::Transformable& obj, Origins origin, const sf::FloatRect& rect)
{
    sf::Vector2f originPos(rect.width, rect.height);
    originPos.x *= ((int)origin % 3) * 0.5f;
    originPos.y *= ((int)origin / 3) * 0.5f;
    obj.setOrigin(originPos);
}

int Utils::Clamp(int val, int min, int max)
{
    return std::max(min, std::min(max, val));
}

float Utils::Clamp(float val, float min, float max)
{
    return std::max(min, std::min(max, val));
}

sf::Vector2f Utils::Clamp(const sf::Vector2f& val, const sf::Vector2f& min, const sf::Vector2f& max)
{
    sf::Vector2f result;
    result.x = Clamp(val.x, min.x, max.x);
    result.y = Clamp(val.y, min.y, max.y);
    return result;
}

float Utils::Lerp(float a, float b, float t, bool clamping)
{
    float v = a + (b - a) * t;
    if (clamping)
    {
        v = Utils::Clamp(v, std::min(a, b), std::max(a, b));
    }
    return v;
}

sf::Vector2f Utils::Lerp(const sf::Vector2f& a, const sf::Vector2f& b, float t, bool clamping)
{
    if (clamping)
    {
        t = Utils::Clamp(t, 0.f, 1.f);
    }

    return a + Utils::Normalize(b - a) * (Utils::Distance(a, b) * t);
}

sf::Color Utils::Lerp(const sf::Color& a, const sf::Color& b, float t, bool clamping)
{
    sf::Color v;
    v.r = Lerp(a.r, b.r, t, clamping);
    v.g = Lerp(a.g, b.g, t, clamping);
    v.b = Lerp(a.b, b.b, t, clamping);
    v.a = Lerp(a.a, b.a, t, clamping);
    return v;
}

sf::Vector2f Utils::Normalize(const sf::Vector2f& vec)
{
    float mag = Magnitude(vec);
    if (mag == 0.f)
    {
        return vec;
    }
    return vec / mag;
}

float Utils::Magnitude(const sf::Vector2f& vec)
{
    return sqrt(vec.x * vec.x + vec.y * vec.y);
}

float Utils::SqrMagnitude(const sf::Vector2f& vec)
{
    return vec.x * vec.x + vec.y * vec.y;
}

float Utils::Distance(const sf::Vector2f& pos1, const sf::Vector2f& pos2)
{
    return Magnitude(pos2 - pos1);
}

float Utils::Angle(const sf::Vector2f& start, const sf::Vector2f end)
{
    return Angle(Normalize(end - start));
}

float Utils::Angle(const sf::Vector2f& direction)
{
    return atan2(direction.y, direction.x) * (180.f / M_PI);
}

//사각형과 원 충돌
bool Utils::IntersectsRectangleAndCircle(const sf::RectangleShape& rectangle, const sf::CircleShape& circle)
{
    sf::FloatRect rectangleBounds = rectangle.getGlobalBounds();
    sf::FloatRect circleBounds = circle.getGlobalBounds();
    sf::Vector2f circleDistance = {
        abs(circle.getPosition().x - rectangle.getPosition().x),
        abs(circle.getPosition().y - rectangle.getPosition().y)
    };
    float radius = circle.getRadius();

    if (circleDistance.x > (rectangleBounds.width / 2 + radius)) { return false; }
    if (circleDistance.y > (rectangleBounds.height / 2 + radius)) { return false; }

    //if (circleDistance.x <= (rectangleBounds.width / 2)) { return true; }
    //if (circleDistance.y <= (rectangleBounds.height / 2)) { return true; }

    float cornerDistance_sq = (circleDistance.x - rectangleBounds.width / 2) * (circleDistance.x - rectangleBounds.width / 2)
        + (circleDistance.y - rectangleBounds.height / 2) * (circleDistance.y - rectangleBounds.height / 2);

    return (cornerDistance_sq <= (radius * radius));
}

//float == 비교
bool Utils::CompareFloat(float lhs, float rhs, float epsilon)
{
    return (fabs(lhs - rhs) < epsilon);
}

//문자열 나누어 vertor로 반환
std::vector<std::string> Utils::splitStrToVec(const std::string& str, const char& delimiter)
{
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string buffer;
    while (getline(ss, buffer, delimiter))
    {
        result.push_back(buffer);
    }
    return result;
}
