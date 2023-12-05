#pragma once
#include <iostream>
#include <fstream>
#include <string>

#include <raylib.h>
#include "nlohmann/json.hpp"

using String = std::string;

class TileMap {
public:
	int width;
	int height;
private:
	int m_Tiles[17][30] = { 0 };
	int m_Collision[17][30] = { 0 };
	Texture2D m_Texture;

public:
	TileMap();

	void Set(int x, int y, int index, bool solid);
	void SetTile(int x, int y, int value);
	void SetSolid(int x, int y, bool value);
	int GetTile(int x, int y);
	bool GetSolid(int x, int y);
	bool LoadFromFile(String path, void (*callback)(String, int, int));
	void Draw();
	void DrawCollision();
	~TileMap();
};

