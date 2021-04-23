#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#ifndef _GAMESCREEN_H
#define _GAMESCREEN_H
class GameScreen
{
protected:

	SDL_Renderer* m_renderer;

public:
	GameScreen(SDL_Renderer* m_renderer);
	~GameScreen();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);


private:
	
};

#endif 

