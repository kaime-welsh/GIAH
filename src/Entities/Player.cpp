#include "Entities/Player.h"

Player::Player(int x, int y) : position(Vector2(x, y)), velocity(Vector2(0, 0)), m_Texture(LoadTexture("res/images/player.png")) {}

void Player::Update(TileMap *map)
{
	// Input Handling
	if (m_CanMove) {
		if (IsKeyDown(KEY_D)) {
			velocity.x = 4;
			m_CanMove = false;
			frame = 1;
			flip = 1;
		}
		else if (IsKeyDown(KEY_A)) {
			velocity.x = -4;
			m_CanMove = false;
			frame = 1;
			flip = -1;
		}
		else if (IsKeyDown(KEY_S)) {
			velocity.y = 4;
			m_CanMove = false;
			frame = 1;
		}
		else if (IsKeyDown(KEY_W)) {
			velocity.y = -4;
			m_CanMove = false;
			frame = 1;
		}
	}

	if (
		map->GetSolid(position.x + velocity.x, position.y + velocity.y) ||
		map->GetSolid(position.x + 7 + velocity.x, position.y + velocity.y) ||
		map->GetSolid(position.x + velocity.x, position.y + 7 + velocity.y) ||
		map->GetSolid(position.x + 7 + velocity.x, position.y + 7 + velocity.y)
		) {
		velocity = Vector2(0, 0);
		m_CanMove = true;
		frame = 0;
	}

	// Apply movement
	position = Vector2Add(position, velocity);
}


void Player::Draw() {
	DrawTexturePro(
		m_Texture,
		Rectangle(frame * 8, 0, 8 * flip, 8),
		Rectangle(position.x, position.y, 8, 8),
		Vector2(0,0), 0.0f, WHITE
	);
}

Player::~Player() {
	UnloadTexture(m_Texture);
}