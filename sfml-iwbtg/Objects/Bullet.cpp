#include "stdafx.h"
#include "Bullet.h"
#include "Scene.h"
#include "SceneMgr.h"

Bullet::Bullet(const std::string id, const std::string n)
	:SpriteGo(id, n)
{
}

Bullet::~Bullet()
{
}

void Bullet::Fire(const sf::Vector2f& pos, const sf::Vector2f& dir, float speed)
{
	sprite.setRotation(Utils::Angle(dir));
	SetPosition(pos);
	direction = dir;
	this->speed = speed;
}

void Bullet::Init()
{
	SpriteGo::Init();
	SetOrigin(Origins::MC);
}

void Bullet::Reset()
{
	SpriteGo::Reset();

	sprite.setRotation(0.f);
	SetPosition(0.f, 0.f);
	direction = { 0.f, 0.f };
	damage = 0;
	range = 2000.f;
}

void Bullet::Release()
{
	SpriteGo::Release();
}

void Bullet::Update(float dt)
{
	SpriteGo::Update(dt);

	range -= speed * dt;
	if (range <= 0.f)
	{
		SCENE_MGR.GetCurrentScene()->RemoveGo(this);
		pool->Return(this);
		return;
	}

	position += direction * speed * dt;
	sprite.setPosition(position);

	//if (sprite.getGlobalBounds().intersects())
	//{
	//	SCENE_MGR.GetCurrentScene()->RemoveGo(this);
	//	pool->Return(this);
	//}
}

void Bullet::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}