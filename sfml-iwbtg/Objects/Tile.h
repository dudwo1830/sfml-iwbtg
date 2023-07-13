#pragma once
#include "VertexArrayGo.h"

class Player;

class Tile : public VertexArrayGo
{
public:
	enum class Types {
		None = -1,
		Normal,
		Killer,
		Througth,
		Fake
	};

protected:
	Types type = Types::None;
	
	Player* player = nullptr;
	
	std::function<void()> CollideTop;
	std::function<void()> CollideLeft;
	std::function<void()> CollideRight;
	std::function<void()> CollideBottom;

	Tile(const Tile& other) = delete;
	bool operator==(const Tile& other) const = delete;
public:
	Tile(const std::string& textureId = "", const std::string& name = "");
	virtual ~Tile();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Update(float deltaTime) override;

	void SetType(Types type);
	Player* GetPlayer();
	void SetPlayer(Player* player);
};

