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

	if (GameState == State::MAIN_MENU) {
		m_Window.setMouseCursorVisible(true);
		
		while (m_Window.pollEvent(m_event)) {
			for (std::list<GUI::Button>::iterator it = m_mainMenuButtons.begin(); it != m_mainMenuButtons.end(); ++it) {
				it->update(m_event, m_Window);
			}
		}
	}
	else if (GameState == State::PLAYING) {
		m_Window.setMouseCursorVisible(false);
		// Handle input specific to Player
		m_Player.handleInput();
	}
	else if (GameState == State::PAUSED) {
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
					GameState = State::PLAYING;
					m_Hud.setGunChargeBackground(m_Player.getMaxCharge()+2.0);
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
					GameState = State::PLAYING;
				}
			}
		}
	}
	else if (GameState == State::SETTINGS) {
		m_Window.setMouseCursorVisible(true);
		// Put Settings Screen Input code here
	}
	else if (GameState == State::LOADING) {
		m_Window.setMouseCursorVisible(false);
		// Put Loading Screen Input code here
	}
}