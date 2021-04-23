#pragma once

#include "Commons.h"
#include "Constants.h"
#include "Texture2D.h"
#include "LevelMap.h"
#include "SDL.h"
#include <iostream>

using namespace std;

#ifndef _CHARACTER_H
#define _CHARACTER_H

class Texture2D;

class Character
{

private:




	LevelMap* m_current_level_map;


protected:

	SDL_Renderer* m_renderer;
	Vector2D m_position;
	Texture2D* m_texture;

	bool m_moving_left;
	bool m_moving_right;
	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);
	
	virtual void AddGravity(float deltaTime);

	virtual void Jump();

	bool m_jumping;
	bool m_can_jump;
	float m_jump_force;
		
	float m_collision_radius;

	bool m_alive;

public:

	Character(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map);
	~Character();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	void SetPosition(Vector2D new_position);
	Vector2D GetPosition();

	float GetCollisionRadius();

	Rect2D GetCollisionBox() { return Rect2D(m_position.x, m_position.y, m_texture->GetWidth(), m_texture->GetHeight()); }

	bool IsJumping() { return m_jumping; }
	void CancelJump() { m_jump_force = 0; }

	FACING m_facing_direction;

	bool GetAlive() { return m_alive; }
	void SetAlive(bool state) { m_alive = state; }
};

#endif

