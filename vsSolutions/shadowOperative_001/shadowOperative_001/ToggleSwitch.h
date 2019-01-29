/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2019/01/29	YYYY/MM/DD
*	@description
*/

#pragma once

#ifndef TOGGLESWITCH_H
#define TOGGLESWITCH_H

#include "SoundManager.h"
#include "TextureHolder.h"

class ToggleSwitch{
public:
	
	ToggleSwitch(sf::Time time, sf::Vector2i spawnPos);
	sf::Sprite getSprite();
	sf::FloatRect getPosition();
	sf::Vector2f getCenter();
	void update(sf::Time elapsedTime, int** m_ArrayLevel);
	bool toggle(sf::Time elapsedTime, SoundManager& m_SM); 

private:
	//Delay between toggle events on switch
	int switchTimeDelay = 3000;
	//enum class of all possible switch states
	enum class ToggleState { TOGGLE_ON, TOGGLE_OFF };
	//Holds the current switch state
	ToggleState m_ToggleState = ToggleState::TOGGLE_OFF;
	//Sprite for switch toggled on
	sf::Sprite m_SpriteToggleOn;
	//Sprite for switch toggled off
	sf::Sprite m_SpriteToggleOff;
	//Holds the position of the switch X*Y
	sf::Vector2f m_Position;
	//track toggle time to create a delay betwen toggle events
	sf::Time m_LastToggleEvent;
};

#endif

