#pragma once
#include "Commons.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#ifndef _GAMESCREENMANAGER_H
#define _GAMESCREENMANAGER_H

class GameScreen;

class GameScreenManager
{

public:

	GameScreenManager(SDL_Renderer* renderer, SCREENS StartScreen);
	~GameScreenManager();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	void ChangeScreen(SCREENS new_screen);

private:

	SDL_Renderer* m_renderer;
	GameScreen* m_Current_Screen;

};

#endif

