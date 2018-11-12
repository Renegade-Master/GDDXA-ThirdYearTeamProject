/**
*	@author			Ciaran Bent [K00221230]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description
*/

#pragma once
#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include <SFML/Graphics.hpp>

class LevelManager {
private:
	sf::Vector2i m_LevelSize;
	sf::Vector2f m_StartPosition;
	float m_TimeModifier = 1;
	float m_BaseTimeLimit = 0;
	int m_CurrentLevel = 0;
	const int NUM_LEVELS = 4;

public:
	const int TILE_SIZE = 50;
	const int VERTS_IN_QUAD = 4;

	float getTimeLimit();

	sf::Vector2f getStartPosition();

	int** nextLevel(sf::VertexArray& rVaLevel);

	sf::Vector2i getLevelSize();

	int getCurrentLevel();
};
#endif // !LEVELMANAGER_H