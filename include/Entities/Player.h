#pragma once
#include <raylib.h>
#include <raymath.h>
#include "TileMap.h"
#include "Entities/Entity.h"

class Player: public Entity
{
public:
	Vector2 position;
	Vector2 velocity;

	int frame = 0;
	int flip = 1;

private:
	Texture2D m_Texture;
	bool m_CanMove = true;

public:
	Player(int x, int y);
	const char* GetName() override { return "Player"; }
	~Player() override;
private:
	void Update(TileMap *map) override;
	void Draw() override;
};