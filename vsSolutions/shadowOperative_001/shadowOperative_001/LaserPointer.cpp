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
void LaserPointer::Spawn(sf::Vector2i startPosition, float gravity, sf::Time gameStart, char dir) {
	this->m_Position = sf::Vector2f(startPosition);
	this->m_Position.x = this->m_Position.x * 50;
	this->m_Position.y = this->m_Position.y * 50;
}
/*
*	Updates the LaserPointer object for current frame
*/
void LaserPointer::update() {
	//to be continued
}