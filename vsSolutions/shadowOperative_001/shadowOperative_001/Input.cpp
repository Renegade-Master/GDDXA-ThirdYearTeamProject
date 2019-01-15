/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description
*/

#include "Engine.h"
#include<iostream>

void Engine::input() {
	sf::Event event;

	if (GameState == State::MAIN_MENU) {
		// Put Main Menu Screen Input code here
	}
	else if (GameState == State::PLAYING) {
		// Handle input specific to Thomas
		if (m_Thomas.handleInput()) {
			// Play a jump sound
			m_SM.playJump();
		}
	}
	else if (GameState == State::PAUSED) {
		while (m_Window.pollEvent(event)) {
			// Maybe replace with nested Switch statement?
			//  GamePad Controls
			if (event.type == sf::Event::JoystickButtonPressed) {
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
			//  Keyboard Controls
			if (event.type == sf::Event::KeyPressed) {
				m_usingController = false;
				// Handle the player quitting
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
					m_Window.close();
				}

				// Handle the player starting the game
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
					//m_Playing = true;
					GameState = State::PLAYING;
				}
			}
		}
	}
	else if (GameState == State::SETTINGS) {
		// Put Settings Screen Input code here
	}
	else if (GameState == State::LOADING) {
		// Put Loading Screen Input code here
	}
}