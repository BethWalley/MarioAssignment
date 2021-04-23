#pragma once

#ifndef _CHARACTERCOIN_H
#define _CHARACTERCOIN_H

#include "Character.h"

class CharacterCoin : public Character
{
public:
	CharacterCoin(SDL_Renderer* renderer, string imagePath, LevelMap* map, FACING start_facing);
	~CharacterCoin();

	void Update(float deltaTime, SDL_Event e);
	void Render();

	Vector2D GetNewLocation();

private:
	void Animate(float deltaTime);

	float m_single_sprite_w;
	float m_single_sprite_h;

	float m_frame_delay;
	int m_current_frame;

	Vector2D m_coin_spawns[5];
};

#endif