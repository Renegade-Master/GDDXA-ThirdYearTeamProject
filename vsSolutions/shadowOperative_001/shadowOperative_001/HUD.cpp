/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description
*/

#include "Hud.h"

Hud::Hud()
{
	sf::Vector2u resolution;
	//resolution.x = sf::VideoMode::getDesktopMode().width;
	//resolution.y = sf::VideoMode::getDesktopMode().height;
	resolution.x = 1280;
	resolution.y = 720;

	// Load the font
	m_Font.loadFromFile("fonts/Roboto-Light.ttf");

	// Paused
	m_StartText.setFont(m_Font);
	m_StartText.setCharacterSize(100);
	m_StartText.setFillColor(sf::Color::White);
	m_StartText.setString("Press Enter when ready!");

	// Position the text
	sf::FloatRect textRect = m_StartText.getLocalBounds();

	m_StartText.setOrigin(textRect.left +
		textRect.width / 2.0f,
		textRect.top +
		textRect.height / 2.0f);

	m_StartText.setPosition(resolution.x / 2.0f, resolution.y / 2.0f);

	// Time
	m_TimeText.setFont(m_Font);
	m_TimeText.setCharacterSize(75);
	m_TimeText.setFillColor(sf::Color::White);
	m_TimeText.setPosition(resolution.x - 150, 0);
	m_TimeText.setString("------");

	// Level
	m_LevelText.setFont(m_Font);
	m_LevelText.setCharacterSize(75);
	m_LevelText.setFillColor(sf::Color::White);
	m_LevelText.setPosition(25, 0);
	m_LevelText.setString("1");
}

sf::Text Hud::getMessage() {
	return m_StartText;
}

sf::Text Hud::getLevel() {
	return m_LevelText;
}

sf::Text Hud::getTime() {
	return m_TimeText;
}

void Hud::setLevel(sf::String text) {
	m_LevelText.setString(text);
}

void Hud::setTime(sf::String text) {
	m_TimeText.setString(text);
}