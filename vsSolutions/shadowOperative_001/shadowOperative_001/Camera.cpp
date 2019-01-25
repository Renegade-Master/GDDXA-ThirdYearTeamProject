#include "Camera.h"
Camera::Camera() {

}
void Camera::spawn(sf::Vector2i startPosition, float gravity, sf::Time gameStart, char dir) {
	this->m_Position = sf::Vector2f(startPosition);
	m_Position.x = m_Position.x * 50;
	m_Position.y = m_Position.y * 50;
	m_Gravity = gravity;
	m_Sprite = sf::Sprite(TextureHolder::GetTexture(
		"graphics/camera.png"));
	std::cout << "\ndir" << dir;
	this->m_Sprite.setOrigin(this->getCenter().x - this->getCenter().x + 50,
		this->getCenter().y - this->getCenter().y + 1);
	if (dir == 'z') {
		std::cout << "\nRotating: z: -90.0f";
		m_Sprite.setRotation(-90.0f);
		rotation = -90.0f;
		rotationStartPoint = -90.0f;
		this->m_Position.y -= 25;
		m_Sprite.setPosition(this->m_Position);
	}
	else if (dir == 'c') {
		std::cout << "\nRotating: c: 90.0f";
		m_Sprite.setRotation(90.0f);
		rotation = 90.0f;
		rotationStartPoint = 90.0f;
		m_Sprite.setPosition(this->m_Position);
	}
	else if (dir == 'v') {
		std::cout << "\nRotating: v: 180.0f";
		m_Sprite.setRotation(180.0f);
		rotation = 180.0f;
		rotationStartPoint = 180.0f;
		this->m_Position.x -= 25;
		m_Sprite.setPosition(this->m_Position);
	}
	else if (dir == 'x') {
		this->m_Position.y += 25;
		this->m_Position.x += 75;
		m_Sprite.setPosition(this->m_Position);
		rotation = 0.0f;
		rotationStartPoint = 0.0f;
	}

	awarenessOfPlayer = 0.0;
	lastDetectionEvent = gameStart;
	detectMeter.setSize(sf::Vector2f(10, this->getAwareness()));
	detectMeter.setFillColor(sf::Color::Red);
	detectMeter.setPosition(this->getCenter().x - 5, this->getCenter().y - 30);
	std::cout << "\n This.getCenter().x: " << this->getCenter().x << ", this->getCenter().y: " << this->getCenter().y;
	
	std::cout << "\nthis->getSprite().getOrigin().x: " << this->getSprite().getOrigin().x
		<< ", this->getSprite().getOrigin().y" << this->getSprite().getOrigin().y;
	//std::cout << "\nThis->get" << this->getSprite().g;
	//m_Sprite.setOrigin(this->getCenter().x, this->getCenter().y);
}
float Camera::getRotation() {
	return rotation;
}
void Camera::update(float elapsedTime, int** m_ArrayLevel) {
	if (concious) {
		if (forward) {
			rotation += 0.5f;
			m_Sprite.setRotation(rotation);
			//std::cout << "\nRotating Forward";
		}
		else {
			rotation -= 0.5f;
			m_Sprite.setRotation(rotation);
			//std::cout << "\nRotating Back";
		}
		if (forward) {
			if (rotation >= rotationStartPoint+20.0f) {
				forward = false;
				//std::cout << "\nForward = false";
			}
		}
		else {
			if (rotation <= rotationStartPoint-20.0f) {
				forward = true;
				//std::cout << "\nForward = true";
			}
		}
		cone.updateCamConePos(this->m_Position, this->detectionDistance,
			this->sightAngle, this->rotation, this->forward);
	}
}
