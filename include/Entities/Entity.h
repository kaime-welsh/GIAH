#pragma once
#include "TileMap.h"

class Entity {
public:
	virtual const char* GetName() = 0;
	virtual void Update(TileMap *map) {}
	virtual void Draw() {}
	virtual ~Entity() {}
};