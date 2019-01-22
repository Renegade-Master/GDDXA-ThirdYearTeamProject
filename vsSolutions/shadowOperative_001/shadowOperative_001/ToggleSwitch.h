#pragma once

#ifndef TOGGLESWITCH_H
#define TOGGLESWITCH_H
#include <SFML/Graphics.hpp>
class ToggleSwitch{
private:
	enum class State { TOGGLE_ON, TOGGLE_OFF };
	State m_ToggleState = State::TOGGLE_OFF;
	sf::Sprite m_Sprite;
	sf::Vector2f m_Position;
	sf::Time m_LastToggleEvent;
public:
	ToggleSwitch(sf::Time time);
	sf::Sprite getSprite();
	sf::FloatRect getPosition();
	sf::Vector2f getCenter();
	void update();
	void toggle(sf::Time elapsedTime);
};
#endif

