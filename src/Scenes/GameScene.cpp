#include <Scenes/GameScene.h>

static TileMap* map;
static std::vector<Entity*> entities;
static Player* player;

static void EntityCallback(String id, int x, int y) {
	if (id == "Player")
	{
		player = new Player(x, y);
		entities.push_back(player);
	}
}

void GameScene::Load() {
	map = new TileMap();
	map->LoadFromFile("test", EntityCallback);
}
void GameScene::Update() {
	for (auto entity : entities) {
		entity->Update(map);
	}
}

void GameScene::Draw() {
	ClearBackground({ 10, 10, 10, 255 });

	map->Draw();

	for (auto entity : entities) {
		entity->Draw();
	}
}

void GameScene::Unload() {
	delete map;

	for (auto entity : entities) {
		delete entity;
	}
	entities.clear();
}