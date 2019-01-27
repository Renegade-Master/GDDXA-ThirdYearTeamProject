#include "LaserPointer.h"

/*
*	Default constructor for LaserPointer
*/
LaserPointer::LaserPointer(){
	m_Sprite = sf::Sprite(TextureHolder::GetTexture(
		"graphics/LaserPointer.png"));
}
/*
*	initialises the variables of the LaserPointer object
*/
void LaserPointer::spawn(sf::Vector2i startPosition, float gravity, sf::Time gameStart, char dir) {
	this->m_Position = sf::Vector2f(startPosition);
	this->m_Position.x = this->m_Position.x * 50;
	this->m_Position.y = this->m_Position.y * 50;

	this->m_Sprite.setOrigin(this->getCenter().x - this->getCenter().x + 50,
		this->getCenter().y - this->getCenter().y + 1);

	if (dir == 'a') {
		this->m_Position.y += 75;
		m_Sprite.setPosition(this->m_Position);
		m_Sprite.setRotation(90.0f);
	}
	else if (dir == 'n') {
		this->m_Position.y -= 25;
		m_Sprite.setPosition(this->m_Position);
		m_Sprite.setRotation(-90.0f);
	}
	else if (dir == 'm') {
		this->m_Position.x += 75;
		m_Sprite.setPosition(this->m_Position);
	}
	else if (dir == 'f') {
		this->m_Position.x -= 25;
		this->m_Position.y += 25;
		m_Sprite.setPosition(this->m_Position);
		m_Sprite.setRotation(180.0f);
	}
	
}
/*
*	Updates the LaserPointer object for current frame
*/
void LaserPointer::update() {
	//to be continued
}