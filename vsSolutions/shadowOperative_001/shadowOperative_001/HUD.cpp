/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
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
	m_isHidden.setFont(m_Font);
	m_isHidden.setCharacterSize(50);
	m_isHidden.setFillColor(sf::Color::White);
	m_isHidden.setPosition(25, 0);
	//m_isHidden.setString("1");

	//StunGun charge
	m_GunChargebackground.setPosition(resolution.x - (resolution.x / 10)-1.0, 10);
	m_GunChargebackground.setFillColor(sf::Color::Black);
	m_GunChargebackground.setOutlineColor(sf::Color::Color(169,169,169,255));
	m_GunChargebackground.setOutlineThickness(4.5);
	m_GunCharge.setPosition(resolution.x - (resolution.x /10), 10);
	m_GunCharge.setFillColor(sf::Color::Yellow);
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
sf::Text Hud::getHidden()
{
	//m_isHidden.setString("Hidden(temp)");
	return m_isHidden;
}
void Hud::setLevel(sf::String text) {
	m_LevelText.setString(text);
}
void Hud::setHidden(int hidden)
{
	switch (hidden)
	{
	case 1:
		m_isHidden.setString("hidden");
		break;
	case 2:
		m_isHidden.setString("Caution");
		break;
	case 3:
		m_isHidden.setString("DETECTED!!!!!");
		break;
	default:
		m_isHidden.setString("????");
		break;
	}
	m_isHidden;
}

void Hud::setTime(sf::String text) {
	m_TimeText.setString(text);
}
void Hud::setGunCharge(float charge)
{
	m_GunCharge.setSize(sf::Vector2f(charge, 30));
}
sf::RectangleShape Hud::getGunCharge()
{
	return m_GunCharge;
}
void Hud::setGunChargeBackground(float maxCharge)
{
	m_GunChargebackground.setSize(sf::Vector2f(maxCharge, 30));
}
sf::RectangleShape Hud::getGunBackground()
{
	return m_GunChargebackground;
}