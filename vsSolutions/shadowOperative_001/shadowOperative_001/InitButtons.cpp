/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description
*/

#include "Engine.h"

void Engine::initButtons() {
	// Make the Main Menu Buttons
	m_mainMenuButtons.push_back(GUI::Button(
		"Play",
		m_buttonFont,
		sf::Vector2f(resolution.x * 0.3f, resolution.y * 0.4f),
		GUI::ButtonStyle::none));
	m_mainMenuButtons.push_back(GUI::Button(
		"Settings",
		m_buttonFont,
		sf::Vector2f(resolution.x * 0.3f, resolution.y * 0.5f),
		GUI::ButtonStyle::none));
	m_mainMenuButtons.push_back(GUI::Button(
		"Quit",
		m_buttonFont,
		sf::Vector2f(resolution.x * 0.3f, resolution.y * 0.7f),
		GUI::ButtonStyle::cancel));

	// Make the Paused Buttons
	m_pausedButtons.push_back(GUI::Button(
		"Play",
		m_buttonFont,
		sf::Vector2f(resolution.x * 0.2f, resolution.y * 0.95f),
		GUI::ButtonStyle::save));
	m_pausedButtons.push_back(GUI::Button(
		"Back",
		m_buttonFont,
		sf::Vector2f(resolution.x * 0.5f, resolution.y * 0.95f),
		GUI::ButtonStyle::cancel));

	// Make the Level Select Buttons
	m_levelSelectButtons.push_back(GUI::Button(
		"Level 1",
		m_buttonFont,
		sf::Vector2f(resolution.x* 0.2f, resolution.y* 0.2f),
		GUI::ButtonStyle::save));
	m_levelSelectButtons.push_back(GUI::Button(
		"Level 2",
		m_buttonFont,
		sf::Vector2f(resolution.x* 0.2f, resolution.y* 0.4f),
		GUI::ButtonStyle::save));
	m_levelSelectButtons.push_back(GUI::Button(
		"Level 3",
		m_buttonFont,
		sf::Vector2f(resolution.x* 0.2f, resolution.y* 0.6f),
		GUI::ButtonStyle::save));
	m_levelSelectButtons.push_back(GUI::Button(
		"Back",
		m_buttonFont,
		sf::Vector2f(resolution.x* 0.5f, resolution.y* 0.95f),
		GUI::ButtonStyle::cancel));

	//	Make the Settings Buttons
	//		All Settings
	m_settingsButtons.push_back(GUI::Button(
		"Graphics",
		m_buttonFont,
		sf::Vector2f(resolution.x * 0.2f, resolution.y * 0.2f),
		GUI::ButtonStyle::none));
	m_settingsButtons.push_back(GUI::Button(
		"Audio",
		m_buttonFont,
		sf::Vector2f(resolution.x* 0.2f, resolution.y* 0.4f),
		GUI::ButtonStyle::none));
	m_settingsButtons.push_back(GUI::Button(
		"Gameplay",
		m_buttonFont,
		sf::Vector2f(resolution.x* 0.2f, resolution.y* 0.6f),
		GUI::ButtonStyle::none));
	m_settingsButtons.push_back(GUI::Button(
		"Back",
		m_buttonFont,
		sf::Vector2f(resolution.x * 0.5f, resolution.y * 0.95f),
		GUI::ButtonStyle::cancel));

	//		Graphics Settings
	m_graphicsSettingsButtons.push_back(GUI::Button(
		"Lock to 30 FPS",
		m_buttonFont,
		sf::Vector2f(resolution.x * 0.3f, resolution.y * 0.33f),
		GUI::ButtonStyle::none));
	m_graphicsSettingsButtons.push_back(GUI::Button(
		"Lock to 60 FPS",
		m_buttonFont,
		sf::Vector2f(resolution.x* 0.7f, resolution.y* 0.33f),
		GUI::ButtonStyle::none));
	m_graphicsSettingsButtons.push_back(GUI::Button(
		"V-Sync ON",
		m_buttonFont,
		sf::Vector2f(resolution.x* 0.3f, resolution.y* 0.66f),
		GUI::ButtonStyle::none));
	m_graphicsSettingsButtons.push_back(GUI::Button(
		"V-Sync OFF",
		m_buttonFont,
		sf::Vector2f(resolution.x* 0.7f, resolution.y* 0.66f),
		GUI::ButtonStyle::none));
	m_graphicsSettingsButtons.push_back(GUI::Button(
		"Back",
		m_buttonFont,
		sf::Vector2f(resolution.x * 0.5f, resolution.y * 0.95f),
		GUI::ButtonStyle::cancel));

	//		Audio Settings
	m_audioSettingsButtons.push_back(GUI::Button(
		"Back",
		m_buttonFont,
		sf::Vector2f(resolution.x * 0.5f, resolution.y * 0.95f),
		GUI::ButtonStyle::cancel));

	//		Gameplay Settings
	m_gameplaySettingsButtons.push_back(GUI::Button(
		"Enable Controller",
		m_buttonFont,
		sf::Vector2f(resolution.x * 0.3f, resolution.y * 0.3f),
		GUI::ButtonStyle::none));
	m_gameplaySettingsButtons.push_back(GUI::Button(
		"Force Disable Controller",
		m_buttonFont,
		sf::Vector2f(resolution.x* 0.7f, resolution.y* 0.3f),
		GUI::ButtonStyle::none));
	m_gameplaySettingsButtons.push_back(GUI::Button(
		"Back",
		m_buttonFont,
		sf::Vector2f(resolution.x * 0.5f, resolution.y * 0.95f),
		GUI::ButtonStyle::cancel));
}