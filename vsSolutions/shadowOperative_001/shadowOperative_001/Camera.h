#pragma once
#ifndef CAMERA_H
#define CAMERA_H
#include "Enemy.h"
class Camera : public Enemy
{
private:
	//Current rotation orientation
	float rotation;
	//is the camera rotating Forward or backward
	bool forward = true;
	//What was the original Angle of Rotation
	float rotationStartPoint;
	//What direction is the camera Facing
	char direction;
public:
	void spawn(sf::Vector2i startPosition, float gravity, sf::Time gameStart,char dir,int** m_ArrayLevel);
	void update(float elapsedTime, int** m_ArrayLevel);
	Camera();
	float getRotation();
	void takeDamage();
	sf::String getClassName();
};
#endif //CAMERA_H
