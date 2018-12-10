/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[]
*					Rory Ryan	[]
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

public:
	Hud();
	sf::Text getMessage();
	sf::Text getLevel();
	sf::Text getTime();

	void setLevel(sf::String text);
	void setTime(sf::String text);
};
#endif // !HUD_H