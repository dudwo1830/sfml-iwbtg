#include "stdafx.h"
#include "SpriteEffect.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "SceneGame.h"
SpriteEffect::SpriteEffect(const std::string& textureId, const std::string& name)
	:SpriteGo(textureId, name)
{
}

void SpriteEffect::Init()
{
	SpriteGo::Init();
	SetOrigin(Origins::MC);
}

void SpriteEffect::Reset()
{
	SpriteGo::Reset();
	timer = 0.f;
	sprite.setColor({255, 255, 255, 255});
}

void SpriteEffect::Update(float deltaTime)
{
	SpriteGo::Update(deltaTime);

	timer += deltaTime;
	UINT8 alpha = Utils::Lerp(255, 0, (timer / duration));
	sprite.setColor({ 255, 255, 255, alpha });
	
	if (timer > duration)
	{
		if (pool != nullptr)
		{
			SCENE_MGR.GetCurrentScene()->RemoveGo(this);
			pool->Return(this);
		}
		else
		{
			SetActive(false);
		}
		
		return;
	}
}