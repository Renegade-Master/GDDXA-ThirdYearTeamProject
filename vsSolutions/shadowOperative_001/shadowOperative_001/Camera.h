#pragma once
#ifndef CAMERA_H
#define CAMERA_H
#include "Enemy.h"
class Camera : public Enemy
{
private:
	float rotation;
	bool forward = true;
	float rotationStartPoint;
	char direction;
public:
	void spawn(sf::Vector2i startPosition, float gravity, sf::Time gameStart,char dir);
	void update(float elapsedTime, int** m_ArrayLevel);
	Camera();
	float getRotation();
	void takeDamage();
};
#endif //CAMERA_H
