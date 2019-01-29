#pragma once

#ifndef TOGGLESWITCH_H
#define TOGGLESWITCH_H
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"
#include<iostream>
#include "soundManager.h"
class ToggleSwitch{
private:
	enum class ToggleState { TOGGLE_ON, TOGGLE_OFF };
	ToggleState m_ToggleState = ToggleState::TOGGLE_OFF;
	sf::Sprite m_SpriteToggleOn;
	sf::Sprite m_SpriteToggleOff;
	sf::Vector2f m_Position;
	/*Create a delayy between toggles so 
	m_Player doesnt toggle in rapid succession*/
	sf::Time m_LastToggleEvent;
public:

	int switchTimeDelay = 3000;
	ToggleSwitch(sf::Time time, sf::Vector2i spawnPos);
	sf::Sprite getSprite();
	sf::FloatRect getPosition();
	sf::Vector2f getCenter();
	void update(sf::Time elapsedTime,int** m_ArrayLevel);
	bool toggle(sf::Time elapsedTime,SoundManager& m_SM);
};
#endif

