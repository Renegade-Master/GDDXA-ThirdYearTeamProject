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
Command* InputHandler::handleInput() {
	if (!m_isControllerN00b) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			return(key_A);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			return(key_D);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			return(key_SPACE);
		}
	}
	else if (m_isControllerN00b) {
		if (sf::Joystick::getAxisPosition(0,sf::Joystick::X) < -10.0f) {
			return(cont_LEFT_STICK_LEFT);
		}
		else if (sf::Joystick::getAxisPosition(0, sf::Joystick::X) > 10.0f) {

		}
	}

	//	Nothing was pressed
	return(NULL);
}