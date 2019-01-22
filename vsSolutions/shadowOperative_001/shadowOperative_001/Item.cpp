/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description
*/

#include "Item.h"
Item::Item(){

}
void Item::spawn() {
	
}
void Item::update(float elapsedTime, int** m_ArrayLevel) {
	this->m_ItemSprite.setPosition(this->m_Position);
}
float Item::getCapacity() {
	std::cout << "\nWe should not be here";
	return 1.0f;
}

sf::FloatRect Item::getPosition() {
	return m_ItemSprite.getGlobalBounds();
}

sf::Vector2f Item::getCenter() {
	return sf::Vector2f(
		m_Position.x + m_ItemSprite.getGlobalBounds().width / 2,
		m_Position.y + m_ItemSprite.getGlobalBounds().height / 2
	);
}

sf::FloatRect Item::getBottom() {
	return m_Bottom;
}

sf::FloatRect Item::getTop() {
	return m_Top;
}

sf::FloatRect Item::getLeft() {
	return m_Left;
}

sf::FloatRect Item::getRight() {
	return m_Right;
}

sf::Sprite Item::getSprite() {
	return m_ItemSprite;
}
/*
void Item::stopRight(float position) {

	m_Position.x = position - m_DoorSprite.getGlobalBounds().width;
	m_Sprite.setPosition(m_Position);
}

void Item::stopLeft(float position) {
	m_Position.x = position + m_DoorSprite.getGlobalBounds().width;
	m_Sprite.setPosition(m_Position);
}*/
Item::~Item() {
}