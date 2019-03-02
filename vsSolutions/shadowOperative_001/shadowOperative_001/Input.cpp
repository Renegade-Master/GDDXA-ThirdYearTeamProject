/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description
*/

#include "Engine.h"

/**
*	Handle the input from the player for this frame
*/
void Engine::input() {
	if (m_GameState == GameState::MAIN_MENU) {
		m_Window.setMouseCursorVisible(true);

		// Handle Buttons
		int i = 0;
		for (std::list<GUI::Button>::iterator it = m_mainMenuButtons.begin(); it != m_mainMenuButtons.end(); ++it) {
			switch (i++) {
			case 0: // Enter Game
				if (it->getState() == GUI::ButtonState::clicked) {
					it->setState(GUI::ButtonState::normal);
					m_SM.playButtonClick();
					m_GameState = GameState::LEVEL_SELECT;
				}
				break;
			case 1: // Settings
				if (it->getState() == GUI::ButtonState::clicked) {
					it->setState(GUI::ButtonState::normal);
					m_SM.playButtonClick();
					m_GameState = GameState::SETTINGS;
					m_SettingsPage = SettingsPage::LIST;
				}
				break;
			case 2: // Quit
				if (it->getState() == GUI::ButtonState::clicked) {
					it->setState(GUI::ButtonState::normal);
					m_SM.playButtonClick();
					m_Window.close();
				}
				break;
			}
		}
	}
	else if (m_GameState == GameState::LEVEL_SELECT) {
		m_Window.setMouseCursorVisible(true);

		// Handle Level Select Buttons
		int i = 0;
		for (std::list<GUI::Button>::iterator it = m_levelSelectButtons.begin(); it != m_levelSelectButtons.end(); ++it) {
			switch (i++) {
			case 0: // Level 1
				if (it->getState() == GUI::ButtonState::clicked) {
					it->setState(GUI::ButtonState::normal);
					m_SM.playButtonClick();
					m_LM.m_CurrentLevel = 1;
					m_GameState = GameState::LOADING;
				}
				break;
			case 1: // Level 2
				if (it->getState() == GUI::ButtonState::clicked) {
					it->setState(GUI::ButtonState::normal);
					m_SM.playButtonClick();
					m_LM.m_CurrentLevel = 2;
					m_GameState = GameState::LOADING;
				}
				break;
			case 2: // Level 3
				if (it->getState() == GUI::ButtonState::clicked) {
					it->setState(GUI::ButtonState::normal);
					m_SM.playButtonClick();
					m_LM.m_CurrentLevel = 3;
					m_GameState = GameState::LOADING;
				}
				break;
			case 3: // Quit
				if (it->getState() == GUI::ButtonState::clicked) {
					it->setState(GUI::ButtonState::normal);
					m_SM.playButtonClick();
					m_GameState = GameState::MAIN_MENU;
				}
				break;
			}
		}
	}
	else if (m_GameState == GameState::LOADING) {
		m_Window.setMouseCursorVisible(false);
		// Put Loading Screen Input code here
	}
	else if (m_GameState == GameState::READYUP) {
		m_Window.setMouseCursorVisible(true);
		while (m_Window.pollEvent(m_event)) {
			//  Keyboard Controls
			if (m_event.type == sf::Event::KeyPressed) {
				// Handle the player quitting
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
					m_Window.close();
				}

				// Handle the player starting the game
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
					m_GameState = GameState::PLAYING;
					m_Hud.setGunChargeBackground(m_Player.getMaxCharge() + 2.0);
				}
			}
		}
	}
	else if (m_GameState == GameState::PLAYING) {
		m_Window.setMouseCursorVisible(false);

		//	Get User input
		Command* cmd = m_IH.handleInput(dt);

		if (cmd) {
			cmd->execute(m_Player);
		}
	}
	else if (m_GameState == GameState::PAUSED) {
		m_Window.setMouseCursorVisible(false);

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
						it->setState(GUI::ButtonState::normal);
						m_SM.playButtonClick();
						m_SettingsPage = SettingsPage::GRAPHICS;
					}
					break;
				case 1: // Audio Settings
					if (it->getState() == GUI::ButtonState::clicked) {
						it->setState(GUI::ButtonState::normal);
						m_SM.playButtonClick();
						m_SettingsPage = SettingsPage::AUDIO;
					}
					break;
				case 2: // Gameplay Settings
					if (it->getState() == GUI::ButtonState::clicked) {
						it->setState(GUI::ButtonState::normal);
						m_SM.playButtonClick();
						m_SettingsPage = SettingsPage::GAMEPLAY;
					}
					break;
				case 3: // Back
					if (it->getState() == GUI::ButtonState::clicked) {
						it->setState(GUI::ButtonState::normal);
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
						it->setState(GUI::ButtonState::normal);
						m_SM.playButtonClick();
						m_frameRate = 30;
						refreshWindow();
					}
					break;
				case 1: // Lock to 60 FPS
					if (it->getState() == GUI::ButtonState::clicked) {
						it->setState(GUI::ButtonState::normal);
						m_SM.playButtonClick();
						m_frameRate = 60;
						refreshWindow();
					}
					break;
				case 2: // Turn V-Sync ON
					if (it->getState() == GUI::ButtonState::clicked) {
						it->setState(GUI::ButtonState::normal);
						m_SM.playButtonClick();
						m_vSyncActive = true;
						m_frameRate = 0; //	(Framerate Limiting && V-Sync) == Bad Time
						refreshWindow();
					}
					break;
				case 3: // Turn V-Sync OFF
					if (it->getState() == GUI::ButtonState::clicked) {
						it->setState(GUI::ButtonState::normal);
						m_SM.playButtonClick();
						m_vSyncActive = false;
						m_frameRate = 0;
						refreshWindow();
					}
					break;
				case 4: // Back
					if (it->getState() == GUI::ButtonState::clicked) {
						it->setState(GUI::ButtonState::normal);
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
				case 0: // Sound Effects Volume Down
					if (it->getState() == GUI::ButtonState::clicked) {
						it->setState(GUI::ButtonState::normal);
						m_SM.playButtonClick();
						if (m_SM.m_SFX_VOLUME >= 10.0f) {
							m_SM.m_SFX_VOLUME -= 10.0f;
						}
						else {
							m_SM.m_SFX_VOLUME = 0.0f;
						}
					}
					break;
				case 1: // Sound Effects Volume Up
					if (it->getState() == GUI::ButtonState::clicked) {
						it->setState(GUI::ButtonState::normal);
						m_SM.playButtonClick();
						if (m_SM.m_SFX_VOLUME <= 90.0f) {
							m_SM.m_SFX_VOLUME += 10.0f;
						}
						else {
							m_SM.m_SFX_VOLUME = 100.0f;
						}
					}
					break;
				case 2: // Music Volume Down
					if (it->getState() == GUI::ButtonState::clicked) {
						it->setState(GUI::ButtonState::normal);
						m_SM.playButtonClick();
						if (m_SM.m_MUSIC_VOLUME >= 10.0f) {
							m_SM.m_MUSIC_VOLUME -= 10.0f;
						}
						else {
							m_SM.m_MUSIC_VOLUME = 0.0f;
						}
					}
					break;
				case 3: // Music Volume Up
					if (it->getState() == GUI::ButtonState::clicked) {
						it->setState(GUI::ButtonState::normal);
						m_SM.playButtonClick();
						if (m_SM.m_MUSIC_VOLUME <= 90.0f) {
							m_SM.m_MUSIC_VOLUME += 10.0f;
						}
						else {
							m_SM.m_MUSIC_VOLUME = 100.0f;
						}
					}
					break;
				case 4: // UI Volume Down
					if (it->getState() == GUI::ButtonState::clicked) {
						it->setState(GUI::ButtonState::normal);
						if (m_SM.m_UI_VOLUME >= 10.0f) {
							m_SM.m_UI_VOLUME -= 10.0f;
						}
						else {
							m_SM.m_UI_VOLUME = 0.0f;
						}
						m_SM.playButtonClick();
					}
					break;
				case 5: // UI Volume Up
					if (it->getState() == GUI::ButtonState::clicked) {
						it->setState(GUI::ButtonState::normal);
						if (m_SM.m_UI_VOLUME <= 90.0f) {
							m_SM.m_UI_VOLUME += 10.0f;
						}
						else {
							m_SM.m_UI_VOLUME = 100.0f;
						}
						m_SM.playButtonClick();
					}
					break;
				case 6: // Back
					if (it->getState() == GUI::ButtonState::clicked) {
						it->setState(GUI::ButtonState::normal);
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
				case 0: // Control Scheme A - Default
					if (it->getState() == GUI::ButtonState::clicked) {
						it->setState(GUI::ButtonState::normal);
						m_SM.playButtonClick();
						m_IH.chooseScheme(ControlScheme::DEFAULT);
					}
					break;
				case 1: // Disable Controller
					if (it->getState() == GUI::ButtonState::clicked) {
						it->setState(GUI::ButtonState::normal);
						m_SM.playButtonClick();
						m_IH.chooseScheme(ControlScheme::BUMPERJUMPER);
					}
					break;
				case 2: // Back
					if (it->getState() == GUI::ButtonState::clicked) {
						it->setState(GUI::ButtonState::normal);
						m_SM.playButtonClick();
						m_SettingsPage = SettingsPage::LIST;
					}
					break;
				}
			}
		}
	}
}