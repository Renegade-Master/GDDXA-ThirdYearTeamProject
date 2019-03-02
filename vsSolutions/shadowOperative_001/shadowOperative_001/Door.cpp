/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description
*/

#include "Door.h"

/**
*	Paramaterised Constructor
*/
Door::Door(char state, sf::Vector2i position) {
	this->m_Position = (sf::Vector2f)position;
	this->m_Position.x = m_Position.x * TILE_SIZE;
	this->m_Position.y = (m_Position.y * TILE_SIZE) - TILE_SIZE ;
	
	if (state == 'D') {
		m_DoorState = State::OPEN;
	}
	else if (state == 'd') {
		m_DoorState = State::CLOSE;
	}
	else if (state == '9') {
		m_DoorState = State::STATIC;
		m_ItemSprite = sf::Sprite(TextureHolder::GetTexture(
			"graphics/DoorStatic.png"));
		m_ItemSprite.setPosition(this->m_Position);
		return;
	}
	m_OpenDoorSprite = sf::Sprite(TextureHolder::GetTexture(
		"graphics/DoorOpen.png"));
	m_ClosedDoorSprite = sf::Sprite(TextureHolder::GetTexture(
		"graphics/DoorLocked.png"));

	m_OpenDoorSprite.setPosition(this->m_Position);
	m_ClosedDoorSprite.setPosition(this->m_Position);
}

/**
*	Alter State when triggered
*/
void Door::doorState() {
	if (m_DoorState == State::STATIC) {
		return;
	}
	if (m_DoorState == State::CLOSE) {
		m_DoorState = State::OPEN;
	}
	else if (m_DoorState == State::OPEN) {
		m_DoorState = State::CLOSE;
	}
}

/**
*	Update Doors
*/
void Door::update(float elapsedTime, int** m_ArrayLevel) {
	if (m_DoorState == State::STATIC) {
		this->m_ItemSprite.setPosition(this->m_Position);
	}
	else {
		this->m_OpenDoorSprite.setPosition(this->m_Position);
		this->m_ClosedDoorSprite.setPosition(this->m_Position);
	}
}

/**
*	Virtual Function need never be called
*/
float Door::getCapacity() {
	//std::cout << "\nWe should not be here";
	return -1.0f;
}

/**
*	Return Sprite
*/
sf::Sprite Door::getDoorSprite() {
	if (m_DoorState == State::STATIC) {
		return m_ItemSprite;
	}
	else if(m_DoorState == State::OPEN){
		return m_OpenDoorSprite;
	}
	else if (m_DoorState == State::CLOSE) {
		return m_ClosedDoorSprite;
	}
}

/**
*	verify wether or not the door is static or changeable
*/
bool Door::getDoorState() {
	if (m_DoorState == State::STATIC) {
		return false;
	}
	else {
		return true;
	}
}

/**
*	Return valid state(Player can pass through)) if the door staye is open
*/
bool Door::getValidState() {
	if (m_DoorState == State::OPEN) {
		return true;
	}
	return false;
}

/**
*	getSprite bounds dependant on object State
*/
sf::FloatRect Door::getPosition() {
	if (m_DoorState == State::STATIC) {
		return m_ItemSprite.getGlobalBounds();
	}
	else if (m_DoorState == State::OPEN) {
		return m_OpenDoorSprite.getGlobalBounds();
	}
	else if (m_DoorState == State::CLOSE) {
		return m_ClosedDoorSprite.getGlobalBounds();
	}
}
