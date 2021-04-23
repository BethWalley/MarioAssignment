#include "GameTitleScreen.h"
#include "Texture2D.h"
#include <iostream>

GameTitleScreen::GameTitleScreen(SDL_Renderer* renderer, GameScreenManager* gsManager) : GameScreen(renderer)
{
	m_screen_manager = gsManager;

	setUpLevel();
}

GameTitleScreen::~GameTitleScreen()
{
	delete m_background_texture;
	m_background_texture = nullptr;
}

void GameTitleScreen::Render()
{
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);
}

void GameTitleScreen::Update(float deltaTime, SDL_Event e)
{
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_SPACE:
			m_screen_manager->ChangeScreen(SCREEN_LEVEL1);
		}
	}
}

bool GameTitleScreen::setUpLevel()
{
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/Title.png"))
	{
		std::cout << "Failed to load title texture!" << std::endl;
		return false;
	}
}
