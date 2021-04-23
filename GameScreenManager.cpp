#include "GameScreenManager.h"
#include "GameScreen.h"
#include "GameScreenLevel1.h"
#include "GameTitleScreen.h"
#include "GameEndScreen.h"
#include <iostream>

using namespace std;

GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS StartScreen)
{
	m_renderer = renderer;
	m_Current_Screen = nullptr;

	ChangeScreen(StartScreen);
}
GameScreenManager::~GameScreenManager()
{
	m_renderer = nullptr;

	delete m_Current_Screen;
	m_Current_Screen = nullptr;
}

void GameScreenManager::Render()
{
	m_Current_Screen->Render();
}

void GameScreenManager::Update(float deltaTime, SDL_Event e)
{
	m_Current_Screen->Update(deltaTime, e);
}

void GameScreenManager::ChangeScreen(SCREENS new_screen)
{
	if (m_Current_Screen != nullptr)
	{
		delete m_Current_Screen;
	}

	GameScreenLevel1* tempScreen;

	GameTitleScreen* tempScreen2;

	GameEndScreen* tempScreen3;
	

	switch (new_screen)
	{
	case SCREEN_TITLE:
		tempScreen2 = new GameTitleScreen(m_renderer, this);
		m_Current_Screen = (GameScreen*)tempScreen2;
		tempScreen2 = nullptr;
		break;
	case SCREEN_END:
		tempScreen3 = new GameEndScreen(m_renderer, this);
		m_Current_Screen = (GameScreen*)tempScreen3;
		tempScreen3 = nullptr;
		break;
	case SCREEN_LEVEL1:
		tempScreen = new GameScreenLevel1(m_renderer, this);
		m_Current_Screen = (GameScreen*)tempScreen;
		tempScreen = nullptr;
		break;
	default:;

	}
}

