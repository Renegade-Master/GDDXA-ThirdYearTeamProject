/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2018/12/11	YYYY/MM/DD
*	@description
*/

#include "ToggleSwitch.h"

/**
*	Default Constructor
*/
ToggleSwitch::ToggleSwitch(sf::Time time, sf::Vector2i spawnPos) {
	this->m_Position = (sf::Vector2f)spawnPos;
	m_Position.x = m_Position.x * TILE_SIZE;
	m_Position.y = m_Position.y * TILE_SIZE;
	m_LastToggleEvent = time;
	m_SpriteToggleOn = sf::Sprite(TextureHolder::GetTexture(
		"graphics/Switch_ToggleOn.png"));
	m_SpriteToggleOff = sf::Sprite(TextureHolder::GetTexture(
		"graphics/Switch_ToggleOn.png"));
	m_SpriteToggleOff.setPosition(this->m_Position);
	m_SpriteToggleOn.setPosition(this->m_Position);
}

/**
*	Choose whcih Sprite to return dependant on State
*/
sf::Sprite ToggleSwitch::getSprite(){
	if (m_ToggleState == ToggleState::TOGGLE_OFF) {
		return m_SpriteToggleOff;
	}
	else {
		return m_SpriteToggleOn;
	}
}

/*
*	Decide which sprite to getPosition of
*/
sf::FloatRect ToggleSwitch::getPosition() {
	if (m_ToggleState == ToggleState::TOGGLE_OFF) {
		return m_SpriteToggleOff.getGlobalBounds();
	}
	else {
		return m_SpriteToggleOn.getGlobalBounds();
	}
}

/*
*	Decide which sprie to get Center of and return coordinates
*/
sf::Vector2f ToggleSwitch::getCenter() {
	if (m_ToggleState == ToggleState::TOGGLE_OFF) {
		return sf::Vector2f(
			m_Position.x + m_SpriteToggleOff.getGlobalBounds().width / 2,
			m_Position.y + m_SpriteToggleOff.getGlobalBounds().height / 2
		);
	}
	else {
		return sf::Vector2f(
			m_Position.x + m_SpriteToggleOn.getGlobalBounds().width / 2,
			m_Position.y + m_SpriteToggleOn.getGlobalBounds().height / 2
		);
	}
}

/*
*	Update the switch location
*/
void ToggleSwitch::update(sf::Time elapsedTime, int** m_ArrayLevel) {
	if (elapsedTime.asMilliseconds() -
		m_LastToggleEvent.asMilliseconds() > switchTimeDelay)
	{
		if (m_ToggleState == ToggleState::TOGGLE_OFF) {
			this->m_SpriteToggleOff.setPosition(this->m_Position);
		}
		else {
			this->m_SpriteToggleOn.setPosition(this->m_Position);
		}
	}
}

/*
*	if switch can be toggled, toggle
*/
bool ToggleSwitch::toggle(sf::Time elapsedTime, SoundManager& m_SM) {
	if (elapsedTime.asMilliseconds() -
		m_LastToggleEvent.asMilliseconds() > switchTimeDelay) {
		m_LastToggleEvent = elapsedTime;
		
		if (m_ToggleState == ToggleState::TOGGLE_OFF) {
			m_ToggleState = ToggleState::TOGGLE_ON;
			m_SM.playButtonClick();
			return true;
		}
		else {
			m_ToggleState = ToggleState::TOGGLE_OFF;
			m_SM.playButtonClick();
			return true;
		}
	}
	return false;
}