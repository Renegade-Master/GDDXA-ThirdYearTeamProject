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
void Item::spawn(sf::Vector2i startPosition) {
	// Place the item at the starting point
	//this->m_Position.x *= 2;
	this->m_Position = (sf::Vector2f)startPosition;
	this->m_Position.x = this->m_Position.x * 50;
	this->m_Position.y = this->m_Position.y;
	
	this->m_ItemSprite.setOrigin(sf::Vector2f(this->getCenter().x, this->getCenter().y));
	this->m_ItemSprite.scale(2.0f, 2.0f);

	m_ItemSprite.setPosition(this->m_Position);
}
void Item::update(float elapsedTime, int** m_ArrayLevel) {
	this->m_ItemSprite.setPosition(this->m_Position);
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