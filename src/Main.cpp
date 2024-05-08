#include <algorithm>
#include <string>
#include <map>

#include <raylib.h>
#include "Common.h"

#include "Scenes/Scene.h"
#include "Scenes/GameScene.h"

static String windowName = "GIAH";
static int screenWidth = 960;
static int screenHeight = 544;
static int width = 240;
static int height = 136;

bool debugDraw = false;

static std::map<String, Scene*> scenes;
static Scene* current_scene;

void ChangeScene(String id) {
	if (scenes.contains(id)) {
		if (current_scene)
			current_scene->Unload();
		current_scene = scenes[id];
		current_scene->Load();
	}
	else
		std::cout << "[ERROR]: No scene found with name '" << id << "'!" << std::endl;
}

int main() {
	// Create window and render texture
	SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
	InitWindow(screenWidth, screenHeight, windowName.c_str());
	SetWindowMinSize(width, height);
	RenderTexture target = LoadRenderTexture(width, height);
	SetTextureFilter(target.texture, TEXTURE_FILTER_POINT);
	SetTargetFPS(60);

	scenes.insert({ "Game", new GameScene() });
	ChangeScene("Game");

	if (current_scene)
		current_scene->Load();

	while (!WindowShouldClose()) {
		// Get screen scaling
		float scale = std::min(
			(float)GetScreenWidth() / width,
			(float)GetScreenHeight() / height
		);

		// Scale mouse to virtual size
		SetMouseOffset(
			-(GetScreenWidth() - (width * scale)) * 0.5f,
			-(GetScreenHeight() - (height * scale)) * 0.5f
		);
		SetMouseScale(1 / scale, 1 / scale);

		// Update Game state
		if (IsKeyPressed(KEY_GRAVE))
			debugDraw = !debugDraw;
		if (current_scene)
			current_scene->Update();

		// Draw Game state
		BeginTextureMode(target);
		ClearBackground(BLACK);
		if (current_scene)
			current_scene->Draw();
		EndTextureMode();

		// Draw render texture
		BeginDrawing();
		ClearBackground(BLACK);
		DrawTexturePro(
			target.texture,
			Rectangle(0.0f, 0.0f, (float)target.texture.width, (float)-target.texture.height),
			Rectangle(
				(GetScreenWidth() - ((float)width * scale)) * 0.5f,
				(GetScreenHeight() - ((float)height * scale)) * 0.5f,
				(float)width * scale, (float)height * scale
				),
			Vector2(0, 0),
			0.0f, WHITE
		);

		if (debugDraw)
			DrawFPS(0, 0);
		EndDrawing();
	}

	// Probably better way to do this
	// Fix later
	for (std::map<String, Scene*>::iterator it = scenes.begin(); it != scenes.end(); it++) {
		delete it->second;
	}
	scenes.clear();

	UnloadRenderTexture(target);
	CloseWindow();
	return 0;
}
