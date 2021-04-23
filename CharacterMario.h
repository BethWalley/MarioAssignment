#pragma once
#include "Character.h"
#include "Texture2D.h"

#ifndef _CHARACTERMARIO_H
#define _CHARACTERMARIO_H

class CharacterMario : public Character
{

public:

	CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map);
	~CharacterMario();

	virtual void Update(float deltaTime, SDL_Event e);
	virtual void Render();

protected:


};

#endif // !_CHARACTERMARIO_H
