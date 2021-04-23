#include "LevelMap.h"
#include <iostream>

LevelMap::LevelMap(int map[MAP_HEIGHT][MAP_WIDTH])
{
	m_map = new int* [MAP_HEIGHT];
	for (unsigned int i = 0; i < MAP_HEIGHT; i++)
	{
		m_map[i] = new int[MAP_WIDTH];
	}

	for (unsigned int i = 0; i < MAP_HEIGHT; i++)
	{
		for (unsigned int j = 0; j < MAP_WIDTH; j++)
		{
			m_map[i][j] = map[i][j];
		}
	}
}

LevelMap::~LevelMap()
{
	for (unsigned int i = 0; i < MAP_HEIGHT; i++)
	{
		delete[]m_map;
	}
}

int LevelMap::GetTileAT(unsigned int h, unsigned int w)
{
	if (h < MAP_HEIGHT && w < MAP_WIDTH)
	{
		return m_map[h][w];
	}

	return 0;
}

void LevelMap::ChangeTileAt(unsigned int row, unsigned int column, unsigned int new_value)
{
	if (row < MAP_HEIGHT && column < MAP_WIDTH)
	{
		m_map[row][column] = new_value;
	}
}

void LevelMap::PrintMap()
{
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			std::cout << m_map[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

