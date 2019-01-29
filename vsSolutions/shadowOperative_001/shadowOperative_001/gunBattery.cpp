/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2019/01/26	YYYY/MM/DD
*	@description	...
*/

#include "GunBattery.h"

/**
*	Default Constructor
*/
gunBattery::gunBattery(sf::Vector2i startPosition){
	//Place the item at the starting point
	this->m_Position = (sf::Vector2f)startPosition;
	this->m_Position.x = (this->m_Position.x * TILE_SIZE);
	this->m_Position.y = (this->m_Position.y * TILE_SIZE) + 35;

	srand(time(NULL));
	m_Capacity = static_cast<Capacity>(rand() % 3);

	if (this->m_Capacity == Capacity::SMALL) {
		m_ItemSprite = sf::Sprite(TextureHolder::GetTexture(
			"graphics\\Batteries\\BATTERY_SMALL.png"));
		std::cout << "\ngraphics\\Batteries\\BATTERY_SMALL.png";
	}
	else if (this->m_Capacity == Capacity::MEDIUM) {
		m_ItemSprite = sf::Sprite(TextureHolder::GetTexture(
			"graphics\\Batteries\\BATTERY_MEDIUM.png"));
		std::cout << "\ngraphics\\Batteries\\BATTERY_MEDIUM.png";
	}
	else if (this->m_Capacity == Capacity::LARGE) {
		m_ItemSprite = sf::Sprite(TextureHolder::GetTexture(
			"graphics\\Batteries\\BATTERY_LARGE.png"));
		std::cout << "\ngraphics\\Batteries\\BATTERY_LARGE.png";
	}
}

/**
*	...
*/
float gunBattery::getCapacity(){
	if (this->m_Capacity == Capacity::SMALL) {
		return 10.00;
	}
	else if (this->m_Capacity == Capacity::MEDIUM) {
		return 25.00;
	}
	else if (this->m_Capacity == Capacity::LARGE) {
		return 50.00;
	}
}

/**
*	...
*/
void gunBattery::update(float elapsedTime, int** m_ArrayLevel) {
	this->m_ItemSprite.setPosition(this->m_Position);
}