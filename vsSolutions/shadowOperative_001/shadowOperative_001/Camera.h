#pragma once
#ifndef CAMERA_H
#define CAMERA_H
CAMERA_H
#include "Enemy.h"
class Camera : public Enemy
{
private:
	float rotation;
	bool forward = true;
public:
	void spawn(sf::Vector2i startPosition, float gravity, sf::Time gameStart,char dir);
	void update(float elapsedTime, int** m_ArrayLevel);
	Camera();
	float getRotation();
};
#endif //CAMERA_H
