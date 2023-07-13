#pragma once
#include "SpriteGo.h"
#include "ObjectPool.h"

class SpriteEffect : public SpriteGo
{
protected:
	float timer = 0.f;
	float duration = 0.f;

	ObjectPool<SpriteEffect>* pool = nullptr;

public:
	SpriteEffect(const std::string& textureId = "", const std::string& name = "");
	virtual ~SpriteEffect() override { };

	void SetDuration(float durationTime) { this->duration = durationTime; }
	void SetPool(ObjectPool<SpriteEffect>* pool) { this->pool = pool; }

	virtual void Init() override;
	virtual void Reset() override;

	virtual void Update(float deltaTime) override;
	
};

