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
	//Where is the laser is shot from and pointing at
	sf::Vector2f laserOrig;
	sf::Vector2f laserDest;
	double laserRange = 500;
public:
	LaserPointer();
	void spawn(sf::Vector2i startPosition, float gravity, sf::Time gameStart, char dir);
	void update();
	sf::ConvexShape getLaser();
};
#endif // !LASERPOINTER_H

