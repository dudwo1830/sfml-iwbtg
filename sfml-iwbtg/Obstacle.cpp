#include "stdafx.h"
#include "Obstacle.h"
#include "Collider.h"

Obstacle::Obstacle(const std::string& textureId, const std::string& name)
    : SpriteGo(textureId, name)
{
}

Obstacle::~Obstacle()
{
}

void Obstacle::SetCollideEvent(std::function<void()> obsEvent)
{
	this->collideEvent = obsEvent;
}

void Obstacle::CollideCheck(const sf::FloatRect& bounds)
{
	if (isHide)
	{
		return;
	}
	sf::FloatRect obsBounds = this->sprite.getGlobalBounds();

	if (obsBounds.intersects(bounds) && collideEvent != nullptr)
	{
		collideEvent();
	}
}

void Obstacle::Init()
{
}

void Obstacle::Release()
{
}

void Obstacle::Reset()
{
	SpriteGo::Reset();
	isHide = defaultHide;
}

void Obstacle::Update(float deltaTime)
{
	if (Utils::CompareFloat(hideTime, 0.f) || !isHide)
	{
		return;
	}

	std::cout << timer << std::endl;
	timer += deltaTime;
	if (timer >= hideTime)
	{
		isHide = false;
		timer = 0.f;
	}
}

void Obstacle::Draw(sf::RenderWindow& window)
{
	if (!isHide)
	{
		window.draw(sprite);
	}
}
