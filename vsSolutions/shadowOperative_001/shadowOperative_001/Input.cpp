/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description
*/

#include "Engine.h"

void Engine::input() {
	//sf::Event m_event;

	if (m_GameState == GameState::MAIN_MENU) {
		m_Window.setMouseCursorVisible(true);

		// Handle Buttons
		int i = 0;
		for (std::list<GUI::Button>::iterator it = m_mainMenuButtons.begin(); it != m_mainMenuButtons.end(); ++it) {
			switch (i++) {
			case 0: // Enter Game
				if (it->getState() == GUI::ButtonState::clicked) {
					m_SM.playButtonClick();
					m_GameState = GameState::PAUSED;
				}
				break;
			case 1: // Settings
				if (it->getState() == GUI::ButtonState::clicked) {
					m_SM.playButtonClick();
					m_GameState = GameState::SETTINGS;
					m_SettingsPage = SettingsPage::LIST;
				}
				break;
			case 2: // Quit
				if (it->getState() == GUI::ButtonState::clicked) {
					m_SM.playButtonClick();
					m_Window.close();
				}
				break;
			}
		}
	}
	else if (m_GameState == GameState::PLAYING) {
		m_Window.setMouseCursorVisible(false);
		// Handle input specific to Player
		m_Player.handleInput();
	}
	else if (m_GameState == GameState::PAUSED) {
		m_Window.setMouseCursorVisible(true);
		while (m_Window.pollEvent(m_event)) {
			// Maybe replace with nested Switch statement?
			//  Keyboard Controls
			if (m_event.type == sf::Event::KeyPressed) {
				m_usingController = false;
				// Handle the player quitting
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
					m_Window.close();
				}

				// Handle the player starting the game
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
					//m_Playing = true;
					m_GameState = GameState::PLAYING;
					m_Hud.setGunChargeBackground(m_Player.getMaxCharge() + 2.0);
				}
			}
			//  GamePad Controls
			else if (m_event.type == sf::Event::JoystickButtonPressed) {
				m_usingController = true;
				// Handle the player quitting
				if (sf::Joystick::isButtonPressed(0, 7)) {
					//std::cout << "Button 0 is Pressed";
					m_Window.close();
				}

				// Handle the player starting the game
				if (sf::Joystick::isButtonPressed(0, 0)) {
					//std::cout << "Button 7 is Pressed";
					//m_Playing = true;
					m_GameState = GameState::PLAYING;
				}
			}
		}
	}
	else if (m_GameState == GameState::SETTINGS) {
		m_Window.setMouseCursorVisible(true);
		// Put Settings Screen Input code here

		//	List all Settings Pages
		if (m_SettingsPage == SettingsPage::LIST) {
			int i = 0;
			for (std::list<GUI::Button>::iterator it = m_settingsButtons.begin(); it != m_settingsButtons.end(); ++it) {
				switch (i++) {
				case 0: // Graphics Settings
					if (it->getState() == GUI::ButtonState::clicked) {
						m_SM.playButtonClick();
						m_SettingsPage = SettingsPage::GRAPHICS;
					}
					break;
				case 1: // Audio Settings
					if (it->getState() == GUI::ButtonState::clicked) {
						m_SM.playButtonClick();
						m_SettingsPage = SettingsPage::AUDIO;
					}
					break;
				case 2: // Gameplay Settings
					if (it->getState() == GUI::ButtonState::clicked) {
						m_SM.playButtonClick();
						m_SettingsPage = SettingsPage::GAMEPLAY;
					}
					break;
				case 3: // Back
					if (it->getState() == GUI::ButtonState::clicked) {
						m_SM.playButtonClick();
						m_GameState = GameState::MAIN_MENU;
					}
					break;
				}
			}
		}
		// List Graphics options
		else if (m_SettingsPage == SettingsPage::GRAPHICS) {
			int i = 0;
			for (std::list<GUI::Button>::iterator it = m_graphicsSettingsButtons.begin(); it != m_graphicsSettingsButtons.end(); ++it) {
				switch (i++) {
				case 0: // Lock to 30 FPS
					if (it->getState() == GUI::ButtonState::clicked) {
						m_SM.playButtonClick();
						m_frameRate = 30;
						refreshWindow();
					}
					break;
				case 1: // Lock to 60 FPS
					if (it->getState() == GUI::ButtonState::clicked) {
						m_SM.playButtonClick();
						m_frameRate = 60;
						refreshWindow();
					}
					break;
				case 2: // Turn V-Sync ON
					if (it->getState() == GUI::ButtonState::clicked) {
						m_SM.playButtonClick();
						m_vSyncActive = true;
						m_frameRate = 0; //	(Framerate Limiting && V-Sync) == Bad Time
						refreshWindow();
					}
					break;
				case 3: // Turn V-Sync OFF
					if (it->getState() == GUI::ButtonState::clicked) {
						m_SM.playButtonClick();
						m_vSyncActive = false;
						m_frameRate = 0;
						refreshWindow();
					}
					break;
				case 4: // Back
					if (it->getState() == GUI::ButtonState::clicked) {
						m_SM.playButtonClick();
						m_SettingsPage = SettingsPage::LIST;
					}
					break;
				}
			}
		}
		// List Audio options
		else if (m_SettingsPage == SettingsPage::AUDIO) {
			int i = 0;
			for (std::list<GUI::Button>::iterator it = m_audioSettingsButtons.begin(); it != m_audioSettingsButtons.end(); ++it) {
				switch (i++) {
				case 0: // Back
					if (it->getState() == GUI::ButtonState::clicked) {
						m_SM.playButtonClick();
						m_SettingsPage = SettingsPage::LIST;
					}
					break;
				}
			}
		}
		// List Gameplay options
		else if (m_SettingsPage == SettingsPage::GAMEPLAY) {
			int i = 0;
			for (std::list<GUI::Button>::iterator it = m_gameplaySettingsButtons.begin(); it != m_gameplaySettingsButtons.end(); ++it) {
				switch (i++) {
				case 0: // Enable Controller
					if (it->getState() == GUI::ButtonState::clicked) {
						m_SM.playButtonClick();
						std::cout << "THE CONTROLLER IS INFERIOR" << std::endl;
					}
					break;
				case 1: // Force Disable Controller
					if (it->getState() == GUI::ButtonState::clicked) {
						m_SM.playButtonClick();
						std::cout << "THE CONTROLLER IS INFERIOR" <<std::endl;
					}
					break;
				case 2: // Back
					if (it->getState() == GUI::ButtonState::clicked) {
						m_SM.playButtonClick();
						m_SettingsPage = SettingsPage::LIST;
					}
					break;
				}
			}
		}
	}
	else if (m_GameState == GameState::LOADING) {
		m_Window.setMouseCursorVisible(false);
		// Put Loading Screen Input code here
	}
}