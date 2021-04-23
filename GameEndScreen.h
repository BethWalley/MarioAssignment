#pragma once
#include "GameScreen.h"
#include "GameScreenManager.h"
#include "Commons.h"
#ifndef _GAMEENDSCREEN_H
#define _GAMEENDSCREEN_H
class Texture2D;

class GameEndScreen : GameScreen
{
public:

	GameEndScreen(SDL_Renderer* renderer, GameScreenManager* gsManager);
	~GameEndScreen();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;

private:

	Texture2D* m_background_texture;
	GameScreenManager* m_screen_manager;

	bool setUpLevel();
};

#endif