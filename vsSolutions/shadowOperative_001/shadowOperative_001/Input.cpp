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
	
	while (m_Window.pollEvent(event)) {
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
				m_Playing = true;
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
				m_Playing = true;
			}
		}
	}

	// Handle input specific to Thomas
	if (m_Thomas.handleInput())	{
		// Play a jump sound
		m_SM.playJump();
	}
}