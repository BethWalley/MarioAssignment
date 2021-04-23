#pragma once
#include "Character.h"
#include "Texture2D.h"

#ifndef _CHARACTERLUIGI_H
#define _CHARACTERLUIGI_H
class CharacterLuigi : public Character
{
public:

	CharacterLuigi(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map);
	~CharacterLuigi();

	virtual void Update(float deltaTime, SDL_Event e);
	virtual void Render();

protected:
};

#endif

