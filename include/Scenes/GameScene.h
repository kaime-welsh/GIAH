#pragma once
#include <vector>

#include <raylib.h>
#include <Common.h>
#include "TileMap.h"

#include "Scenes/Scene.h"

#include "Entities/Entity.h"
#include "Entities/Player.h"

class GameScene : public Scene
{
public:
	void Load() override;
	void Update() override;
	void Draw() override;
	void Unload() override;
	~GameScene() override { Unload(); }
};