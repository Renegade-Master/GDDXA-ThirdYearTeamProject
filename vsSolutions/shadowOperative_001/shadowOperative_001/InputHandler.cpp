/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2019/01/27	YYYY/MM/DD
*	@description
*/

#include "InputHandler.h"

/**
*	Default Constructor
*/
InputHandler::InputHandler() {
	chooseScheme(ControlScheme::DEFAULT);
}

/**
*	Paramaterised Constructor
*/
void InputHandler::chooseScheme(sf::Uint32 scheme) {

	if (scheme == ControlScheme::DEFAULT) {
		//	Keyboard Keys we want to use
		key_W = nullptr;
		key_A = new cmd_RunLeft();
		key_S = nullptr;
		key_D = new cmd_RunRight();
		key_SPACE = new cmd_Jump();

		//	Mouse Buttons we want to use
		mouse_LMB = new cmd_Shoot();
		mouse_RMB = new cmd_ToggleAim();

		//	Gamepad Buttons we want to use
		cont_CROSS = new cmd_Jump();
		cont_SQUARE = new cmd_Shoot();
		cont_TRIANGLE = nullptr;
		cont_CIRCLE = new cmd_ToggleAim();

		cont_L1 = nullptr;
		cont_L2 = nullptr;
		cont_R1 = nullptr;
		cont_R2 = nullptr;

		cont_LEFT_STICK_LEFT = new cmd_RunLeft();
		cont_LEFT_STICK_RIGHT = new cmd_RunRight();
		cont_LEFT_STICK_UP = nullptr;
		cont_LEFT_STICK_DOWN = nullptr;

		//Control Aiming(Right Analog)
		cont_RIGHT_STICK_LEFT = new cmd_AimLeft;
		cont_RIGHT_STICK_RIGHT = new cmd_AimRight;
		cont_RIGHT_STICK_UP = new cmd_AimUp;
		cont_RIGHT_STICK_DOWN = new cmd_AimDown;
	}
	else if (scheme == ControlScheme::BUMPERJUMPER) {
		//	Keyboard Keys we want to use
		key_W = nullptr;
		key_A = new cmd_RunLeft();
		key_S = nullptr;
		key_D = new cmd_RunRight();
		key_SPACE = new cmd_Jump();

		//	Mouse Buttons we want to use
		mouse_LMB = new cmd_Shoot();
		mouse_RMB = new cmd_ToggleAim();

		//	Gamepad Buttons we want to use
		cont_CROSS = nullptr;
		cont_SQUARE = nullptr;
		cont_TRIANGLE = nullptr;
		cont_CIRCLE = nullptr;

		cont_L1 = new cmd_ToggleAim();
		cont_L2 = nullptr;
		cont_R1 = new cmd_Jump();
		cont_R2 = new cmd_Shoot();

		cont_LEFT_STICK_LEFT = new cmd_RunLeft();
		cont_LEFT_STICK_RIGHT = new cmd_RunRight();
		cont_LEFT_STICK_UP = nullptr;
		cont_LEFT_STICK_DOWN = nullptr;

		cont_RIGHT_STICK_LEFT = nullptr;
		cont_RIGHT_STICK_RIGHT = nullptr;
		cont_RIGHT_STICK_UP = nullptr;
		cont_RIGHT_STICK_DOWN = nullptr;
	}
}

/**
*	Convert User input into Game Commands
*/
Command* InputHandler::handleInput(sf::Time t) {
	m_sinceLastInput += t;
	
	if (m_sinceLastInput > m_inputBlocker) {
		m_sinceLastInput = sf::Time::Zero;
		
		//	Keyboard Keys
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

		//	Gamepad Joysticks
		//		Left Stick
		if (sf::Joystick::getAxisPosition(0, sf::Joystick::X) < -10.0f) {
			return(cont_LEFT_STICK_LEFT);
		}
		if (sf::Joystick::getAxisPosition(0, sf::Joystick::X) > 10.0f) {
			return(cont_LEFT_STICK_RIGHT);
		}
		if (sf::Joystick::getAxisPosition(0, sf::Joystick::Y) < -10.0f) {
			return(cont_LEFT_STICK_UP);
		}
		if (sf::Joystick::getAxisPosition(0, sf::Joystick::Y) > 10.0f) {
			return(cont_LEFT_STICK_DOWN);
		}

		//		Right Stick
		if (sf::Joystick::getAxisPosition(0, sf::Joystick::U) < -10.0f) {
			return(cont_RIGHT_STICK_LEFT);
		}
		if (sf::Joystick::getAxisPosition(0, sf::Joystick::U) > 10.0f) {
			return(cont_RIGHT_STICK_RIGHT);
		}
		if (sf::Joystick::getAxisPosition(0, sf::Joystick::V) < -10.0f) {
			return(cont_RIGHT_STICK_UP);
		}
		if (sf::Joystick::getAxisPosition(0, sf::Joystick::V) > 10.0f) {
			return(cont_RIGHT_STICK_DOWN);
		}

		//	Triggers
		if (sf::Joystick::getAxisPosition(0, sf::Joystick::Z) > 40.0f) {
			return(cont_L2);
		}
		if (sf::Joystick::getAxisPosition(0, sf::Joystick::Z) < -40.0f) {
			return(cont_R2);
		}

		//	Buttons
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
		if (sf::Joystick::isButtonPressed(0, 4)) {
			return(cont_L1);
		}
		if (sf::Joystick::isButtonPressed(0, 5)) {
			return(cont_R1);
		}
	}

	//	Nothing was pressed
	return(noInput);
}