#include "GameEndScreen.h"
#include "Texture2D.h"
#include <iostream>

GameEndScreen::GameEndScreen(SDL_Renderer* renderer, GameScreenManager* gsManager) : GameScreen(renderer)
{
    m_screen_manager = gsManager;

    setUpLevel();
}

GameEndScreen::~GameEndScreen()
{
    delete m_background_texture;
    m_background_texture = nullptr;
}

void GameEndScreen::Render()
{
    m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);
}

void GameEndScreen::Update(float deltaTime, SDL_Event e)
{

}

bool GameEndScreen::setUpLevel()
{
    m_background_texture = new Texture2D(m_renderer);
    if (!m_background_texture->LoadFromFile("Images/End.png"))
    {
        std::cout << "Failed to load title texture!" << std::endl;
        return false;
    }
}
