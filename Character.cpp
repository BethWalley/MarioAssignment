#include "Character.h"


Character::Character(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map)
{
	m_renderer = renderer;
	m_position = start_position;
	m_facing_direction == FACING_RIGHT;
	m_texture = new Texture2D(m_renderer);
	m_moving_left = false;
	m_moving_right = false;
	m_collision_radius = 15.0f;
	m_current_level_map = map;
	m_alive = true;

	if (!m_texture->LoadFromFile(imagePath))
	{
		std::cout << "Failed to load background texture!" << std::endl;
	}
}

Character::~Character()
{
	m_renderer = nullptr;
}

void Character::Render()
{
	if (m_alive)
	{
		if (m_facing_direction == FACING_RIGHT)
		{
			m_texture->Render(m_position, SDL_FLIP_NONE);
		}
		else if (m_facing_direction == FACING_LEFT)
		{
			m_texture->Render(m_position, SDL_FLIP_HORIZONTAL);
		}
		else if (m_facing_direction == FACING_UP)
		{
			m_texture->Render(m_position, SDL_FLIP_NONE);
		}
		else if (m_facing_direction == FACING_DOWN)
		{
			m_texture->Render(m_position, SDL_FLIP_VERTICAL);
		}
	}
}

void Character::Update(float deltaTime, SDL_Event e)
{
	if (m_alive)
	{
		int centralX_position = (int)(m_position.x + (m_texture->GetWidth() * 0.5)) / TILE_WIDTH;
		int foot_position = (int)(m_position.y + m_texture->GetHeight()) / TILE_HEIGHT;

		if (m_current_level_map->GetTileAT(foot_position, centralX_position) == 0)
		{
			AddGravity(deltaTime);
		}
		else
		{
			m_can_jump = true;
		}


		if (m_jumping)
		{
			m_position.y -= m_jump_force * deltaTime;
			m_jump_force -= JUMP_FORCE_DECREMENT * deltaTime;

			if (m_jump_force <= 0.0f)
			{
				m_jumping = false;
			}
		}

		if (m_moving_left)
		{
			MoveLeft(deltaTime);
		}
		else if (m_moving_right)
		{
			MoveRight(deltaTime);
		}

	}
}

void Character::MoveLeft(float deltaTime)
{
	m_position.x -= deltaTime * MOVEMENTSPEED;
	m_facing_direction = FACING_LEFT;
}

void Character::MoveRight(float deltaTime)
{
	m_position.x += deltaTime * MOVEMENTSPEED;
	m_facing_direction = FACING_RIGHT;
}

void Character::Jump()
{
	if (!m_jumping)
	{
		m_jump_force = INITIAL_JUMP_FORCE;
		m_jumping = true;
		m_can_jump = false;
	}
}

void Character::AddGravity(float deltaTime)
{
	if (m_position.y  + 64 <= SCREEN_HEIGHT)
	{
		m_position.y += GRAVITY * deltaTime;
	}
	else
	{
		m_can_jump = true;
	}
}

void Character::SetPosition(Vector2D new_position)
{
	m_position = new_position;
}

Vector2D Character::GetPosition()
{
	return m_position;
}

float Character::GetCollisionRadius()
{
	return m_collision_radius;
}