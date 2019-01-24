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
	m_Sprite.setPosition(this->m_Position);
	if (dir == 'z') {
		std::cout << "\nRotating: z: -90.0f";
		m_Sprite.setRotation(-90.0f);
	}
	else if (dir == 'c') {
		std::cout << "\nRotating: c: 90.0f";
		m_Sprite.setRotation(90.0f);
	}
	else if (dir == 'v') {
		std::cout << "\nRotating: v: 90.0f";
		m_Sprite.setRotation(90.0f);
	}

	awarenessOfPlayer = 0.0;
	lastDetectionEvent = gameStart;
	detectMeter.setSize(sf::Vector2f(10, this->getAwareness()));
	detectMeter.setFillColor(sf::Color::Red);
	detectMeter.setPosition(this->getCenter().x - 5, this->getCenter().y - 30);
}
float Camera::getRotation() {
	return rotation;
}
void Camera::update(float elapsedTime, int** m_ArrayLevel) {
	if (concious) {
		//update if concious
	}
}
