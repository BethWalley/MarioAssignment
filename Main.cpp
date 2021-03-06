#include <SDL.h>

#include <SDL_image.h>

#include <SDL_mixer.h>

#include <iostream>

#include "Constants.h"

#include "Texture2D.h"

#include "Commons.h"

#include "GameScreenManager.h"

using namespace std;

GameScreenManager* game_screen_manager;
Uint32 g_old_time;
SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;
Mix_Music* g_music = nullptr;
//Texture2D*  
bool InitSDL();
void CloseSDL();
bool Update();
void Render();
void LoadMusic(string filePath);

int main(int argc, char* args[])
{
	if (InitSDL())
	{
		LoadMusic("Music/Mario.mp3");
		if (Mix_PlayingMusic() == 0)
		{
			Mix_PlayMusic(g_music, -1);
		}
		game_screen_manager = new GameScreenManager(g_renderer, SCREEN_TITLE);
		g_old_time = SDL_GetTicks();

		bool quit = false;

		while (!quit)
		{
			Render();
			quit = Update();
		}
	}
	

	CloseSDL();

	return 0;
}

bool InitSDL()
{
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL did not initialise. Error: " << SDL_GetError() << endl;
		return false;
	}
	else
	{
		g_window = SDL_CreateWindow
		(
			"Games Engine Creation",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN
		);
		if (g_window == nullptr)
		{
			cout << "Window not created. Error: " << SDL_GetError() << endl;
			return false;
		}
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		cout << "Mixer could not init. Error: " << Mix_GetError();
		return false;
	}
	g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
	if (g_renderer != nullptr)
	{
		int imageFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imageFlags) & imageFlags))
		{
			cout << "SDL Image could not initialise. Error: " << IMG_GetError() << endl;
			return false;
		}
	}
	else
	{
		cout << "Renderer could not initialise. Error: " << SDL_GetError() << endl;
		return false;
	}
	

}

void CloseSDL()
{
	SDL_DestroyWindow(g_window);
	g_window = nullptr;

	IMG_Quit();
	SDL_Quit();

	//release renderer
	SDL_DestroyRenderer(g_renderer);
	g_renderer = nullptr;

	//release texture
	delete game_screen_manager;
	game_screen_manager = nullptr;

	Mix_FreeMusic(g_music);
	g_music = nullptr;
}

bool Update()
{
	Uint32 new_time = SDL_GetTicks();

	SDL_Event e;

	SDL_PollEvent(&e);

	switch (e.type)
	{
	case SDL_QUIT:
		return true;
		break;
	}

	game_screen_manager->Update((float)(new_time - g_old_time) / 1000.0f, e);
	g_old_time = new_time;
	return false;
		
}

void Render()
{
	//clear screen
	SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(g_renderer);

	game_screen_manager->Render();
	
	//update the screen
	SDL_RenderPresent(g_renderer);
}

void LoadMusic(string filePath)
{
	g_music = Mix_LoadMUS(filePath.c_str());
	if (g_music == nullptr)
	{
		cout << "Failed to load music. Error" << Mix_GetError() << endl;
	}

}



