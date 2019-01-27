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
#include "Camera.h"
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

	//Camera
	std::list<sf::Vector2i> m_CameraPosition;
	std::list<char> m_CameraType;

	//LaserPointer
	std::list<sf::Vector2i> m_LaserPointerPos;
	std::list<char> m_LaserDir;

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

	//Enemies
	sf::Vector2i getStartPosition();
	sf::Vector2i getEnemyPosition();
	int getNumOfEnemies();

	int** nextLevel(sf::VertexArray& rVaLevel);
	sf::Vector2i getLevelSize();
	int getCurrentLevel();
	//Items
	int getNumOfItems();
	char getItemType();
	sf::Vector2i getItemPos();
	//Door
	int getNumOfDoors();
	sf::Vector2i getDoorPos();
	char getDoorType();

	//switch
	int getNumSwitches();
	sf::Vector2i getSwitchPos();
	//Camera
	int getNumCams();
	sf::Vector2i getCamPos();
	char getCamDir();
	//Laserpointer
	int getNumLaserPointers();
	sf::Vector2i getLaserPos();
	char getLaserDir();
};
#endif // !LEVELMANAGER_H