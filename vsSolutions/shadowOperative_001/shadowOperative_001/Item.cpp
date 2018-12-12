/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956K00218956]
*					Rory Ryan	[]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description
*/

#include "Item.h"

void Item::spawn(sf::Vector2i startPosition, float gravity) {
	// Place the item at the starting point
	m_Position.x = startPosition.x;
	m_Position.y = startPosition.y;

	// Move the sprite in to position
	m_Sprite.setPosition(m_Position);

}

void Item::update(float elapsedTime, int** m_ArrayLevel) {
	// Overridden
}

sf::FloatRect Item::getPosition() {
	return m_Sprite.getGlobalBounds();
}

sf::Vector2f Item::getCenter() {
	return sf::Vector2f(
		m_Position.x + m_Sprite.getGlobalBounds().width / 2,
		m_Position.y + m_Sprite.getGlobalBounds().height / 2
	);
}

sf::FloatRect Item::getBottem() {
	return m_Bottem;
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
	return m_Sprite;
}

void Item::stopRight(float position) {

	m_Position.x = position - m_Sprite.getGlobalBounds().width;
	m_Sprite.setPosition(m_Position);
}

void Item::stopLeft(float position) {
	m_Position.x = position + m_Sprite.getGlobalBounds().width;
	m_Sprite.setPosition(m_Position);
}