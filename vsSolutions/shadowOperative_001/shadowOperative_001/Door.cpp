/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description
*/

#include "Door.h"

Door::Door(char state, sf::Vector2i position) {
	this->m_Position.x = position.x * 50;
	this->m_Position.y = position.y * 50;
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
	m_OpenDoorSprite.setPosition(this->m_Position);
	m_ClosedDoorSprite = sf::Sprite(TextureHolder::GetTexture(
		"graphics/DoorLocked.png"));
	m_ClosedDoorSprite.setPosition(this->m_Position);
}
void Door::DoorState(){
	if (m_DoorState == State::STATIC) {
		return;
	}
	if (m_DoorState == State::OPEN) {
		m_DoorState = State::CLOSE;
	}
	else if (m_DoorState == State::OPEN) {
		m_DoorState = State::CLOSE;
	}
}
void Door::update(float elapsedTime, int** m_ArrayLevel) {
	if (m_DoorState == State::STATIC) {
		this->m_ItemSprite.setPosition(this->m_Position);
	}
	else {
		this->m_OpenDoorSprite.setPosition(this->m_Position);
		this->m_ClosedDoorSprite.setPosition(this->m_Position);
	}
}
float Door::getCapacity() {
	std::cout << "\nWe should not be here";
	return 1.0f;
}
sf::Sprite Door::getDoorSprite() {
	if (m_DoorState == State::STATIC) {
		return m_ClosedDoorSprite;
	}
	else if(m_DoorState == State::OPEN){
		return m_OpenDoorSprite;
	}
	else if (m_DoorState == State::CLOSE) {
		return m_ClosedDoorSprite;
	}
}

