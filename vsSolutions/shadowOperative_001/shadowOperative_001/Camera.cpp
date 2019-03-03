/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2019/01/15	YYYY/MM/DD
*	@description
*/

#include "Camera.h"

/*
*	Default Constructor for camera object
*/
Camera::Camera() {

}

/*
*	Initialises the variables of this object at beginning of game
*/
void Camera::spawn(sf::Vector2i startPosition, float gravity, sf::Time gameStart, char dir,int** m_ArrayLevel) {
	this->m_Position = sf::Vector2f(startPosition);
	m_Position.x = m_Position.x * TILE_SIZE;
	m_Position.y = m_Position.y * TILE_SIZE;
	m_Gravity = gravity;
	
	m_Sprite = sf::Sprite(TextureHolder::GetTexture(
		"graphics/camera.png"));
	//std::cout << "\ndir" << dir;
	
	this->m_Sprite.setOrigin(this->getCenter().x - this->getCenter().x + TILE_SIZE,
		this->getCenter().y - this->getCenter().y + 1);
	
	if (dir == 'z') {//DOWN
		m_Sprite.setRotation(-90.0f);
		rotation = -90.0f;
		rotationStartPoint = -90.0f;
		this->m_Position.y -= 25;
		this->direction = 'n';
		this->detectionDistance = reCalculateMaxRange(
			this->direction, m_ArrayLevel, this->maxDistance);
		this->direction = 'z';
		m_Sprite.setPosition(this->m_Position);
	}
	else if (dir == 'c') {//UP
		m_Sprite.setRotation(90.0f);
		rotation = 90.0f;
		rotationStartPoint = 90.0f;
		this->direction = 'a';
		this->detectionDistance = reCalculateMaxRange(
			this->direction, m_ArrayLevel, this->maxDistance);
		this->direction = 'c';
		m_Sprite.setPosition(this->m_Position);
	}
	else if (dir == 'v') {//RIGHT
		m_Sprite.setRotation(180.0f);
		rotation = 180.0f;
		rotationStartPoint = 180.0f;
		this->m_Position.x -= 25;
		this->direction = 'f';
		this->detectionDistance = reCalculateMaxRange(
			this->direction, m_ArrayLevel, this->maxDistance);
		this->direction = 'v';
		m_Sprite.setPosition(this->m_Position);
	}
	else if (dir == 'x') {//LEFT
		this->m_Position.y += 25;
		this->m_Position.x += 75;
		this->direction = 'm';
		this->detectionDistance = reCalculateMaxRange(
			this->direction, m_ArrayLevel, this->maxDistance);
		this->direction = 'x';
		m_Sprite.setPosition(this->m_Position);
		rotation = 0.0f;
		rotationStartPoint = 0.0f;
	}
	
	awarenessOfPlayer = 0.0;
	lastDetectionEvent = gameStart;
	detectMeter.setSize(sf::Vector2f(10, this->getAwareness()));
	detectMeter.setFillColor(sf::Color::Red);
	detectMeter.setPosition(this->getCenter().x - 5, this->getCenter().y - 30);	
	this->m_Direction = Direction::LEFT;
}

/*
*	Return the rotation of the camera object
*/
float Camera::getRotation() {
	return rotation;
}

/*
*	Update the Camera object for this frame
*/
void Camera::update(float elapsedTime, int** m_ArrayLevel) {
	if (concious) {
		detectMeter.setSize(sf::Vector2f(10, (-this->getAwareness()) / 2));
		detectMeter.setPosition(this->getCenter().x + 15, this->getCenter().y + 30);
			if (m_Direction != Direction::DETECTION) {
				if (forward) {
					rotation += 0.5f;
					m_Sprite.setRotation(rotation);
				}
				else {
					rotation -= 0.5f;
					m_Sprite.setRotation(rotation);
				}
				if (forward) {
					if (rotation >= rotationStartPoint + 20.0f) {
						forward = false;
					}
				}
				else {
					if (rotation <= rotationStartPoint - 20.0f) {
						forward = true;
					}
				}
			}
			cone.updateCamConePos(this->m_Position, this->detectionDistance,
				this->sightAngle, this->rotation, this->forward, this->direction);
	}

	this->regen(elapsedTime);
}

/*
*	Camera takes Damage from bullet Collision
*/
void Camera::takeDamage() {
	if (this->isConscious()) {
		concious = false;
		this->health = 0;
	}
	else {
		health = 0;
	}
}

/*
*	Return the class Name for this class
*/
sf::String Camera::getClassName() {
	return(sf::String("Camera"));
}
