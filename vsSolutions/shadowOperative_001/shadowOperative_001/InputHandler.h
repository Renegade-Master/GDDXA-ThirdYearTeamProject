/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2019/01/27	YYYY/MM/DD
*	@description
*/

#pragma once
#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include "Command.h"

namespace ControlScheme {
	enum {
		DEFAULT = 0,
		BUMPERJUMPER = 1
	};
}

class InputHandler {
public:
	InputHandler();
	void chooseScheme(sf::Uint32);
	Command* handleInput(sf::Time t);

	//  Is the Player using a controller?
	unsigned int m_controllerIndex = 0;
	sf::Time m_inputBlocker = sf::milliseconds(10);
	sf::Time m_sinceLastInput = sf::Time::Zero;
	sf::Time m_LastToggleEvent = sf::Time::Zero;

private:
	sf::Uint32 m_ControlScheme = ControlScheme::DEFAULT;
	
	//	Null command
	Command* noInput = new cmd_Null();

	//	Keyboard Keys we want to use
	// KeyBoard command 'W'
	Command* key_W = nullptr;
	// KeyBoard command 'A'
	Command* key_A = nullptr;
	// KeyBoard command 'S'
	Command* key_S = nullptr;
	// KeyBoard command 'D'
	Command* key_D = nullptr;
	// KeyBoard command 'SPACE'
	Command* key_SPACE = nullptr;

	//	Mouse Buttons we want to use
	// Mouse command 'Left Click'
	Command* mouse_LMB = nullptr;
	// Mouse command 'Right Click'
	Command* mouse_RMB = nullptr;

	//	Gamepad Buttons we want to use
	// GamePad Command 'x'
	Command* cont_CROSS = nullptr;
	// GamePad Command 'Square'
	Command* cont_SQUARE = nullptr;
	// GamePad Command 'Triangle'
	Command* cont_TRIANGLE = nullptr;
	// GamePad Command 'Circle'
	Command* cont_CIRCLE = nullptr;
	// GamePad Command 'Left Trigger 1'
	Command* cont_L1 = nullptr;
	// GamePad Command 'Left Trigger 2'
	Command* cont_L2 = nullptr;
	// GamePad Command 'Right Trigger 1'
	Command* cont_R1 = nullptr;
	// GamePad Command 'Right Trigger 2'
	Command* cont_R2 = nullptr;
	// GamePad Command 'Left Analog - Left'
	Command* cont_LEFT_STICK_LEFT = nullptr;
	// GamePad Command 'Left Analog - Right'
	Command* cont_LEFT_STICK_RIGHT = nullptr;
	// GamePad Command 'Left Analog - Up';
	Command* cont_LEFT_STICK_UP = nullptr;
	// GamePad Command 'Left Analog - Down';
	Command* cont_LEFT_STICK_DOWN = nullptr;
	// GamePad Command 'Right Analog - Left';
	Command* cont_RIGHT_STICK_LEFT = nullptr;
	// GamePad Command 'Right Analog - Right';
	Command* cont_RIGHT_STICK_RIGHT = nullptr;
	// GamePad Command 'Right Analog - Up';
	Command* cont_RIGHT_STICK_UP = nullptr;
	// GamePad Command 'Right Analog - Down';
	Command* cont_RIGHT_STICK_DOWN = nullptr;
	// GamePad Command 'Right Analog - Left/UP';
	Command* cont_RIGHT_STICK_LEFT_UP = nullptr;
	// GamePad Command 'Right Analog - Left/DOWN';
	Command* cont_RIGHT_STICK_LEFT_DOWN = nullptr;
	// GamePad Command 'Right Analog - Right/UP';
	Command* cont_RIGHT_STICK_RIGHT_UP = nullptr;
	// GamePad Command 'Right Analog - Right/DOWN';
	Command* cont_RIGHT_STICK_RIGHT_DOWN = nullptr;
};

#endif // !INPUTHANDLER_H


