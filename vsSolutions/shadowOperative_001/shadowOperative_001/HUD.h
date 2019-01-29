/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description
*/

#pragma once
#ifndef HUD_H
#define HUD_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Hud {
private:
	//Font for text displayed on the HUD
	sf::Font m_Font;
	//Text displayed at the start of the game on the HUD
	sf::Text m_StartText;
	//Text displays the passed time in the game on the HUD
	sf::Text m_TimeText;
	//Text displays the current level on the HUD
	sf::Text m_LevelText;
	//Text displays whether or not the player is detected
	sf::Text m_isHidden;
	//RectangleShape which size represents the current power level of the players weapon
	sf::RectangleShape m_GunCharge;
	//RectangleShape that is positioned behind the gunCharge to highlight the max charge even when charge is low
	sf::RectangleShape m_GunChargeBackground;
public:
	Hud();
	sf::Text getMessage();
	sf::Text getLevel();
	sf::Text getTime();

	sf::Text getHidden();
	void setHidden(sf::Text text);

	void setGunCharge(float charge);
	sf::RectangleShape getGunCharge();
	void setGunChargeBackground(float maxCharge);
	sf::RectangleShape getGunBackground();

	void setLevel(sf::String text);
	void setTime(sf::String text);

};
#endif // !HUD_H