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

class LaserPointer :public Enemy {
public:
	LaserPointer();
	void spawn(sf::Vector2i startPosition, float gravity, sf::Time gameStart, char dir, int** m_ArrayLevel);
	void update(sf::Time m_GameTimeTotal, SoundManager& m_SM);
	sf::ConvexShape getLaser();
	bool isActive();
	sf::String getClassName();

private:
	//Where is the laser is shot from 
	//Where is the laser shot from 
	sf::Vector2f laserOrig;
	
	//Where is the laser pointing at
	sf::Vector2f laserDest;
	
	//Is the laser currently active?
	bool active;
	
	//When is the last Time the Laser turned on/off
	sf::Time lastToggleEvent;
	//The Laser object fired by The LaserPointer
	laser visionLaser;
	//The range of the Laser
	double laserRange = 500;
	//Max Range of the Laser = laserRange Default
	double maxLaserRange;
};
#endif // !LASERPOINTER_H

