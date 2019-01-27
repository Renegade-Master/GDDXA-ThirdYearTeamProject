#pragma once
#ifndef LASERPOINTER_H
#define LASERPOINTER_H

#include"Enemy.h"

class LaserPointer :public Enemy {
private:
	sf::Vector2f m_Position;
public:
	LaserPointer();
	void Spawn(sf::Vector2i startPosition, float gravity, sf::Time gameStart, char dir);
	void update();
};
#endif // !LASERPOINTER_H

