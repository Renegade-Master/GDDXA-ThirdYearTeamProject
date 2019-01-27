/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2019/01/27	YYYY/MM/DD
*	@description
*/

#include "InputHandler.h"

/**
*	Convert User input into Game Commands
*/
Command* InputHandler::handleInput(sf::Time t) {
	m_sinceLastInput += t;
	
	if (m_sinceLastInput > m_inputBlocker) {
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			return(key_A);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			return(key_D);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			return(key_SPACE);
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			return(mouse_LMB);
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			return(mouse_RMB);
		}

		if (sf::Joystick::getAxisPosition(0, sf::Joystick::X) < -10.0f) {
			return(cont_LEFT_STICK_LEFT);
		}
		if (sf::Joystick::getAxisPosition(0, sf::Joystick::X) > 10.0f) {
			return(cont_LEFT_STICK_RIGHT);
		}
		if (sf::Joystick::isButtonPressed(0, 0)) {
			return(cont_CROSS);
		}
		if (sf::Joystick::isButtonPressed(0, 1)) {
			return(cont_CIRCLE);
		}
		if (sf::Joystick::isButtonPressed(0, 2)) {
			return(cont_SQUARE);
		}
		if (sf::Joystick::isButtonPressed(0, 3)) {
			return(cont_TRIANGLE);
		}
	}

	//	Nothing was pressed
	return(noInput);
}