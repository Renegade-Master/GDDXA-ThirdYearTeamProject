/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description
*/

#include "Item.h"

/**
*	Default Constructor
*/
Item::Item() {

}

/**
*	Destructor
*/
Item::~Item() {
}

/**
*	...
*/
void Item::spawn() {
	
}

/**
*	The function set the position of the sprite to the item.
*/
void Item::update(float elapsedTime, int** m_ArrayLevel) {
	this->m_ItemSprite.setPosition(this->m_Position);
}

/**
*	...
*/
float Item::getCapacity() {
	std::cout << "\nWe should not be here";
	return 1.0f;
}

/**
*	This gets the posititon of the item. 
*/
sf::FloatRect Item::getPosition() {
	return m_ItemSprite.getGlobalBounds();
}

/**
*	This function gets the center of the sprite.
*/
sf::Vector2f Item::getCenter() {
	return sf::Vector2f(
		m_Position.x + m_ItemSprite.getGlobalBounds().width / 2,
		m_Position.y + m_ItemSprite.getGlobalBounds().height / 2
	);
}

/**
*	This function gets the item sprite.
*/
sf::Sprite Item::getSprite() {
	return m_ItemSprite;
}