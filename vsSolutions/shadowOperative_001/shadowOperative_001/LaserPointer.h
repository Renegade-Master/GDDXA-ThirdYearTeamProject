/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description
*/
#pragma once
#ifndef LASERPOINTER_H
#define LASERPOINTER_H

#include"Enemy.h"
#include"laser.h"

class LaserPointer :public Enemy {
private:
	sf::Vector2f m_Position;
	//Laser fired from this object
	laser securityLaser;
	//Where is the laser is shot from 
	sf::Vector2f laserOrig;
	//Where is the laser pointing at
	sf::Vector2f laserDest;
	//what is the maximum distance of the laser
	double maxLaserRange;
	//what is the current maximum distance of the laser
	double laserRange = 500;
	//Is the laser currently active?
	bool active;
	//When is the last Time the Laser turned on/off
	sf::Time lastToggleEvent;
public:
	LaserPointer();
	void spawn(sf::Vector2i startPosition, float gravity, sf::Time gameStart, char dir,int** m_ArrayLevel);
	void update(sf::Time m_GameTimeTotal);
	sf::ConvexShape getLaser();
	bool isActive();
	double reCalculateMaxRange(char dir,int** m_ArrayLevel);
};
#endif // !LASERPOINTER_H

