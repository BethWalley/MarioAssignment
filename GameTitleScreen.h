#pragma once
#include "GameScreen.h"
#include "GameScreenManager.h"
#include "Commons.h"
#ifndef _GAMETITLESCREEN_H
#define _GAMETITLESCREEN_H

class Texture2D;

class GameTitleScreen : GameScreen
{
public:

	GameTitleScreen(SDL_Renderer* renderer, GameScreenManager* gsManager);
	~GameTitleScreen();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;

private:

	Texture2D* m_background_texture;
	GameScreenManager* m_screen_manager;

	bool setUpLevel();
};

#endif
