#include "GameScreenLevel1.h"

#include <iostream>

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer, GameScreenManager* gsManager) : GameScreen(renderer)
{
	m_level_map = nullptr;
	m_screen_manager = gsManager;
	setUpLevel();

}

GameScreenLevel1::~GameScreenLevel1()
{
	delete m_background_texture;
	m_background_texture = nullptr;

	delete mario;
	mario = nullptr;

	delete luigi;
	luigi = nullptr;

	delete m_pow_block;
	m_pow_block = nullptr;

	delete coin;
	coin = nullptr;

	m_enemies.clear();
}

void GameScreenLevel1::Render()
{
	m_background_texture->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE);

	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->Render();
	}

	mario->Render();
	luigi->Render();
	coin->Render();

	m_pow_block->Render();



}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	if (m_screenshake)
	{
		m_shake_time -= deltaTime;
		m_wobble++;
		m_background_yPos = sin(m_wobble);
		m_background_yPos *= 3.0f;

		if (m_shake_time <= 0.0f)
		{
			m_shake_time = false;
			m_background_yPos = 0.0f;
		}
	}

	m_koopa_spawn_timer -= deltaTime;
	if (m_koopa_spawn_timer <= 0.0f)
	{
		CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
		CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_SPEED);
		m_koopa_spawn_timer = KOOPA_SPAWN_TIME;
	}

	mario->Update(deltaTime, e);
	luigi->Update(deltaTime, e);
	coin->Update(deltaTime, e);
	UpdatePOWBlock();
	UpdateEnemies(deltaTime, e);
	UpdateCoin(deltaTime);

	if (mario->GetAlive() == false && luigi->GetAlive() == false)
	{
		std::cout << "Game Over!" << std::endl;

		m_screen_manager->ChangeScreen(SCREEN_END);
		return;
	}

	if (Collisions::Instance()->Circle(mario, luigi))
	{
		std::cout << "Cirlce hit!" << std::endl;
	}

	if (Collisions::Instance()->Box(mario->GetCollisionBox(), luigi->GetCollisionBox()))
	{
		std::cout << "Box hit!" << std::endl;
	}
}

void GameScreenLevel1::UpdatePOWBlock()
{
	if (m_pow_block->IsAvailable()) 
	{
		if (Collisions::Instance()->Box(mario->GetCollisionBox(), m_pow_block->GetCollisionBox()))
		{
			std::cout << "Mario hit pow block" << std::endl;
			if (mario->IsJumping())
			{
				DoScreenShake();
				m_pow_block->TakeHit();
				mario->CancelJump();
			}
		}

		if (Collisions::Instance()->Box(luigi->GetCollisionBox(), m_pow_block->GetCollisionBox()))
		{
			std::cout << "Luigi hit pow block" << std::endl;
			if (luigi->IsJumping())
			{
				DoScreenShake();
				m_pow_block->TakeHit();
				luigi->CancelJump();
			}
		}
	}
}

bool GameScreenLevel1::setUpLevel()
{
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/Level1Background.png"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}

	SetLevelMap();

	mario = new CharacterMario(m_renderer, "Images/Mario.png", Vector2D(64, 330), m_level_map);
	if (mario == nullptr)
	{
		std::cout << "Error: " << SDL_GetError << std::endl;
	}
	luigi = new CharacterLuigi(m_renderer, "images/Luigi.png", Vector2D(128, 330), m_level_map);
	if (luigi == nullptr)
	{
		std::cout << "Error: " << SDL_GetError << std::endl;
	}
	m_pow_block = new PowBlock(m_renderer, m_level_map);
	m_koopa_spawn_timer = KOOPA_SPAWN_TIME;
	coin = new CharacterCoin(m_renderer, "Images/Coin.png", m_level_map, FACING_RIGHT);

	CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
	CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_SPEED);

	m_screenshake = false;
	m_background_yPos = 0.0f;
}

void GameScreenLevel1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = 
	{{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
	{1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};

	if (m_level_map != nullptr)
	{
		delete m_level_map;
	}

	m_level_map = new LevelMap(map);
}

void GameScreenLevel1::DoScreenShake()
{
	m_screenshake = true;
	m_shake_time = SHAKE_DURATION;
	m_wobble = 0.0f;

	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->TakeDamage();
	}
}

void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e)
{
	if (!m_enemies.empty())
	{
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < m_enemies.size(); i++)
		{
			if (m_enemies[i]->GetPosition().y < 300.0f)
			{
				if (m_enemies[i]->GetPosition().x < 0.0f ||
					m_enemies[i]->GetPosition().x + m_enemies[i]->GetCollisionBox().width * 0.5 > SCREEN_WIDTH)
				{
					if (m_enemies[i]->m_facing_direction == FACING_LEFT)
					{
						m_enemies[i]->SetPosition(Vector2D(m_enemies[i]->GetPosition().x + 5, m_enemies[i]->GetPosition().y));
						m_enemies[i]->m_facing_direction = FACING_RIGHT;
					}
					else
					{
						m_enemies[i]->SetPosition(Vector2D(m_enemies[i]->GetPosition().x - 5, m_enemies[i]->GetPosition().y));
						m_enemies[i]->m_facing_direction = FACING_LEFT;
					}
				}
			}
			else
			{
				if (m_enemies[i]->GetPosition().x < 0.0f ||
					m_enemies[i]->GetPosition().x + m_enemies[i]->GetCollisionBox().width * 0.5 > SCREEN_WIDTH)
				{
					m_enemies[i]->SetAlive(false);
				}
			}
			m_enemies[i]->Update(deltaTime, e);

			if ((m_enemies[i]->GetPosition().y > 300.0f || m_enemies[i]->GetPosition().y <= 64.0f) && (m_enemies[i]->GetPosition().x < 64.0f ||
				m_enemies[i]->GetPosition().x > SCREEN_WIDTH - 96.0f))
			{

			}
			else
			{
				if (Collisions::Instance()->Circle(m_enemies[i], mario))
				{
					if (m_enemies[i]->GetInjured())
					{
						m_enemies[i]->SetAlive(false);
					}
					else
					{
						mario->SetAlive(false);
					}

				}
				if (Collisions::Instance()->Circle(m_enemies[i], luigi))
				{
					if (m_enemies[i]->GetInjured())
					{
						m_enemies[i]->SetAlive(false);
					}
					else
					{
						luigi->SetAlive(false);
					}
				}
			}
			if (!m_enemies[i]->GetAlive())
			{
				enemyIndexToDelete = i;
			}
		}
		if (enemyIndexToDelete != -1)
		{
			m_enemies.erase(m_enemies.begin() + enemyIndexToDelete);
		}
	}
}

void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	CharacterKoopa* newKoopa = new CharacterKoopa(m_renderer, "Images/Koopa.png", m_level_map, position, direction, speed);
	m_enemies.push_back(newKoopa);
}

void GameScreenLevel1::UpdateCoin(float deltaTime)
{
	if (Collisions::Instance()->Circle(coin, mario) || Collisions::Instance()->Circle(coin, luigi))
	{
		coin->SetPosition(coin->GetNewLocation());
	}
}


