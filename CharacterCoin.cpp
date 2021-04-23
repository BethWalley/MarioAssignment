#include "CharacterCoin.h"

CharacterCoin::CharacterCoin(SDL_Renderer* renderer, string imagePath, LevelMap* map, FACING start_facing) : Character(renderer, imagePath, Vector2D(0,0), map)
{
	m_single_sprite_w = m_texture->GetWidth() / 3;
	m_single_sprite_h = m_texture->GetHeight();

	m_coin_spawns[0] = Vector2D(200, 200);
	m_coin_spawns[1] = Vector2D(100, 200);
	m_coin_spawns[2] = Vector2D(200, 100);
	m_coin_spawns[3] = Vector2D(200, 300);
	m_coin_spawns[4] = Vector2D(300, 200);

	m_position = GetNewLocation();
}

CharacterCoin::~CharacterCoin()
{

}

void CharacterCoin::Update(float deltaTime, SDL_Event e)
{
	Animate(deltaTime);
}

void CharacterCoin::Render()
{
	if (m_alive == true)
	{
		int left = m_single_sprite_w * m_current_frame;


		SDL_Rect Portion_of_sprite = { left, 0, m_single_sprite_w, m_single_sprite_h };

		SDL_Rect destRect = { (int)(m_position.x), (int)(m_position.y), m_single_sprite_w, m_single_sprite_h };

		m_texture->Render(Portion_of_sprite, destRect, SDL_FLIP_NONE);
	}
}

Vector2D CharacterCoin::GetNewLocation()
{
	return m_coin_spawns[rand() % 5];
}

void CharacterCoin::Animate(float deltaTime)
{
	m_frame_delay -= deltaTime;
	if (m_frame_delay <= 0.0f)
	{
		m_frame_delay = ANIMATION_DELAY;

		m_current_frame++;

		if (m_current_frame > 2)
		{
			m_current_frame = 0;
		}
	}
}
