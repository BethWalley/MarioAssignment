#pragma once
#include <vector>
#include "GameScreen.h"
#include "GameScreenManager.h"
#include "Character.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "CharacterKoopa.h"
#include "CharacterCoin.h"
#include "Commons.h"
#include "LevelMap.h"
#include "Texture2D.h"
#include "Collisions.h"
#include "PowBlock.h"
#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H


class Texture2D;
class Character;
class PowBlock;


class GameScreenLevel1 : GameScreen
{
protected:

public:

	GameScreenLevel1(SDL_Renderer* renderer, GameScreenManager* gsManager);
	~GameScreenLevel1();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;

	void UpdatePOWBlock();

private:

	Texture2D* m_background_texture;

	CharacterMario* mario;
	CharacterLuigi* luigi;
	CharacterCoin* coin;

	LevelMap* m_level_map;

	PowBlock* m_pow_block;

	GameScreenManager* m_screen_manager;

	bool setUpLevel();

	void SetLevelMap();

	bool m_screenshake;
	float m_shake_time;
	float m_wobble;
	float m_background_yPos;

	float m_koopa_spawn_timer;

	void DoScreenShake();

	void UpdateEnemies(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);

	void UpdateCoin(float deltaTime);

	vector<CharacterKoopa*> m_enemies;
};

#endif

