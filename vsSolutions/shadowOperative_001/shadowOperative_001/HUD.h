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

class Hud {
private:
	sf::Font m_Font;
	sf::Text m_StartText;
	sf::Text m_TimeText;
	sf::Text m_LevelText;

	sf::Text m_isHidden;

	sf::RectangleShape m_GunCharge;
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