/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description
*/

#include "Engine.h"

void Engine::initButtons() {
	// Make the Main Menu Buttons
	m_mainMenuButtons.push_back((GUI::Button(
		"Play",
		m_buttonFont,
		sf::Vector2f(resolution.x * 0.3, resolution.y * 0.4),
		GUI::Style::none)));
	m_mainMenuButtons.push_back((GUI::Button(
		"Settings",
		m_buttonFont,
		sf::Vector2f(resolution.x * 0.3, resolution.y * 0.5),
		GUI::Style::none)));
	m_mainMenuButtons.push_back((GUI::Button(
		"Quit",
		m_buttonFont,
		sf::Vector2f(resolution.x * 0.3, resolution.y * 0.7),
		GUI::Style::cancel)));

	// Make the Paused Buttons
	m_pausedButtons.push_back((GUI::Button(
		"Play",
		m_buttonFont,
		sf::Vector2f(resolution.x * 0.2, resolution.y * 0.95),
		GUI::Style::none)).getPointer());
	m_pausedButtons.push_back((GUI::Button(
		"Back",
		m_buttonFont,
		sf::Vector2f(resolution.x * 0.5, resolution.y * 0.95),
		GUI::Style::cancel)).getPointer());

	//	Make the Settings Buttons
	//		All Settings
	m_settingsButtons.push_back((GUI::Button(
		"Play",
		m_buttonFont,
		sf::Vector2f(resolution.x * 0.2, resolution.y * 0.95),
		GUI::Style::none)).getPointer());
	m_settingsButtons.push_back((GUI::Button(
		"Back",
		m_buttonFont,
		sf::Vector2f(resolution.x * 0.5, resolution.y * 0.95),
		GUI::Style::cancel)).getPointer());

	//		Graphics Settings
	m_graphicsSettingsButtons.push_back((GUI::Button(
		"Back",
		m_buttonFont,
		sf::Vector2f(resolution.x * 0.5, resolution.y * 0.95),
		GUI::Style::cancel)).getPointer());

	//		Audio Settings
	m_audioSettingsButtons.push_back((GUI::Button(
		"Back",
		m_buttonFont,
		sf::Vector2f(resolution.x * 0.5, resolution.y * 0.95),
		GUI::Style::cancel)).getPointer());

	//		Gameplay Settings
	m_gameplaySettingsButtons.push_back((GUI::Button(
		"Back",
		m_buttonFont,
		sf::Vector2f(resolution.x * 0.5, resolution.y * 0.95),
		GUI::Style::cancel)).getPointer());
}