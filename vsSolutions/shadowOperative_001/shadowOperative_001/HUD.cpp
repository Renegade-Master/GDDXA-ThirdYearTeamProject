/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description
*/

#include "Hud.h"

/**
*	Default Constructor
*/
Hud::Hud() {
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
	m_StartText.setString("Press Enter to BEGIN!");

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
	m_isHidden.setFont(m_Font);
	m_isHidden.setCharacterSize(50);
	m_isHidden.setFillColor(sf::Color::White);
	m_isHidden.setPosition(25, 0);
	m_isHidden.setString("1");

	//StunGun charge
	m_GunChargeBackground.setPosition(resolution.x - (resolution.x / 10) - 1.0, 10);
	m_GunChargeBackground.setFillColor(sf::Color::Black);
	m_GunChargeBackground.setOutlineColor(sf::Color::Color(169, 169, 169, 255));
	m_GunChargeBackground.setOutlineThickness(4.5);
	m_GunCharge.setPosition(resolution.x - (resolution.x / 10), 10);
	m_GunCharge.setFillColor(sf::Color::Yellow);
}

/**
*	Return the Start Message for the game
*/
sf::Text Hud::getMessage() {
	return m_StartText;
}

/**
*	Return the current m_IsHidden sf::Text variable
*/
sf::Text Hud::getHidden() {
	return m_isHidden;
}

/**
*	Set the current Level Text value
*/
void Hud::setLevel(sf::String text) {
	m_LevelText.setString(text);
}

/**
*	Set the current m_IsHidden value
*/
void Hud::setHidden(sf::Text text)
{
	m_isHidden.setString(text.getString());
}

/**
*	Set the current value for m_TimeText
*/
void Hud::setTime(sf::String text) {
	m_TimeText.setString(text);
}

/**
*	set the current size of RectangleShape m_GunCharge based upon current Gun Energy Level
*/
void Hud::setGunCharge(float charge) {
	m_GunCharge.setSize(sf::Vector2f(charge, 30));
}

/**
*	Return the RectangleShape that is m_GunCharge which represents the current gun charge
*/
sf::RectangleShape Hud::getGunCharge() {
	return m_GunCharge;
}

/**
*	Set The RectangleShape m_GunChargeBackground which m_GunCharge overlays
*/
void Hud::setGunChargeBackground(float maxCharge) {
	m_GunChargeBackground.setSize(sf::Vector2f(maxCharge, 30));
}

/**
*	Return the RectangleShape that is m_GunChargeBackground that m_GunCharge overlays
*/
sf::RectangleShape Hud::getGunBackground() {
	return m_GunChargeBackground;
}