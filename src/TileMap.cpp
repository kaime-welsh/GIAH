#include "TileMap.h"

TileMap::TileMap() : width(30), height(17), m_Texture(LoadTexture("res/images/tiles.png")) { }

#pragma region Setters
void TileMap::Set(int x, int y, int index, bool solid) {
	SetTile(x, y, index);
	SetSolid(x, y, solid);
}

void TileMap::SetTile(int x, int y, int value) {
	m_Tiles[y][x] = value;
}

void TileMap::SetSolid(int x, int y, bool value) {
	m_Collision[y][x] = value;
}
#pragma endregion

#pragma region Getters
int TileMap::GetTile(int x, int y) {
	return m_Tiles[y][x];
}

bool TileMap::GetSolid(int x, int y) {
	return m_Collision[y / 8][x / 8];
}
#pragma endregion

bool TileMap::LoadFromFile(String path, void (*callback)(String, int, int)) {
	// Reset Map
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			SetTile(x, y, 0);
		}
	}

	// Open file
	std::fstream f("res/data/levels/" + path + ".json");
	if (!f) {
		std::cout << "FAILED TO LOAD MAP!" << std::endl;
		return false;
	}

	// Parse JSON data
	nlohmann::json data = nlohmann::json::parse(f);

	// Populate Map
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			int tileData = data["layers"][1]["data2D"][y][x];
			int collisionData = data["layers"][2]["data2D"][y][x];
			Set(x, y, tileData, collisionData);
		}
	}

	nlohmann::json entityLayer = data["layers"][0]["entities"];
	for (nlohmann::json entity : entityLayer) {
		callback(entity["name"], entity["x"], entity["y"]);
	}

	return true;
}

void TileMap::Draw() {
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			DrawTextureRec(
				m_Texture,
				Rectangle(m_Tiles[y][x] * 8, 0, 8, 8),
				Vector2(x * 8, y * 8),
				WHITE
			);
		}
	}
}

void TileMap::DrawCollision() {
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (m_Collision[y][x]) {
				DrawRectangleLines(
					x * 8, y * 8,
					8, 8,
					RED
				);
			}
		}
	}
}
#pragma endregion

TileMap::~TileMap() {
	UnloadTexture(m_Texture);
}