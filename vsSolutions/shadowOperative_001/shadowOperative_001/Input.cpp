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

			if (sf::Joystick::isButtonPressed(0, 0))
			{
				std::cout << "\nIs Jumping";
			}
			if (sf::Joystick::isButtonPressed(0, 2))
			{
				std::cout << "\nCrouching";
			}
			if (sf::Joystick::isButtonPressed(0, 4))
			{
				std::cout << "\nInteract";
			}
			if (sf::Joystick::isButtonPressed(0, sf::Joystick::Y))
			{
				if ((sf::Joystick::getAxisPosition(0, sf::Joystick::Y) > 3.0) ||
					(sf::Joystick::getAxisPosition(0, sf::Joystick::Y) < -3.0))
					std::cout << "\nMovement Direction: Y";
			}
			if (sf::Joystick::isButtonPressed(0, sf::Joystick::X))
			{
				if((sf::Joystick::getAxisPosition(0,sf::Joystick::X)>3.0)|| 
					(sf::Joystick::getAxisPosition(0, sf::Joystick::X) < -3.0))
				std::cout << "\nMovement Direction: X";
			}

			
		}
		//  Keyboard Controls
		if (event.type == sf::Event::KeyPressed) {
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