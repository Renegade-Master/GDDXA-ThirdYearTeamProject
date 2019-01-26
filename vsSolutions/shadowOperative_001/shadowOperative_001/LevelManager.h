/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description
*/

#pragma once
#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include <fstream>
#include <iostream>
#include <list>

#include <SFML/Graphics.hpp>


class LevelManager {
private:
	sf::Vector2i m_LevelSize;
	sf::Vector2i m_StartPosition;
	sf::Vector2i m_EndPosition;
	std::list<sf::Vector2i> m_EnemyPosition;

	//Item creation Data
	std::list<sf::Vector2i> m_ItemPosition;
	std::list<char> m_ItemType;
	//Door Creation Data
	std::list<sf::Vector2i> m_DoorPosition;
	std::list<char> m_DoorType;
	//switch
	std::list<sf::Vector2i> m_SwitchPosition;
	float m_TimeModifier = 1;
	float m_BaseTimeLimit = 0;
	const int NUM_LEVELS = 2;


public:
	LevelManager();
	//~LevelManager();

	const int TILE_SIZE = 50;
	const int VERTS_IN_QUAD = 4;
	float getTimeLimit();

	int m_CurrentLevel = 1;

	sf::Vector2i getStartPosition();
	sf::Vector2i getEnemyPosition();
	int getNumOfEnemies();

	int** nextLevel(sf::VertexArray& rVaLevel);
	sf::Vector2i getLevelSize();
	int getCurrentLevel();

	int getNumOfItems();
	char getItemType();
	sf::Vector2i getItemPos();

	int getNumOfDoors();
	sf::Vector2i getDoorPos();
	char getDoorType();

	//switch
	int getNumSwitches();
	sf::Vector2i getSwitchPos();
};
#endif // !LEVELMANAGER_H