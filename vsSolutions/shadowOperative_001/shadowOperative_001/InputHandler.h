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

class InputHandler {
public:
	Command* handleInput(sf::Time t);

	//  Is the Player using a controller?
	//bool m_isControllerN00b = true;
	unsigned int m_controllerIndex = 0;
	sf::Time m_inputBlocker = sf::milliseconds(500);
	sf::Time m_sinceLastInput = sf::Time::Zero;

private:
	//	Keyboard Keys we want to use
	Command* key_W;
	Command* key_A = new cmd_RunLeft();
	Command* key_S;
	Command* key_D = new cmd_RunRight();
	Command* key_SPACE = new cmd_Jump();

	//	Mouse Buttons we want to use
	Command* mouse_LMB;
	Command* mouse_RMB;

	//	Gamepad Buttons we want to use
	Command* cont_CROSS = new cmd_Jump();
	Command* cont_SQUARE;
	Command* cont_TRIANGLE;
	Command* cont_CIRCLE;

	Command* cont_LEFT_STICK_LEFT = new cmd_RunLeft();
	Command* cont_LEFT_STICK_RIGHT = new cmd_RunRight();
	Command* cont_LEFT_STICK_UP;
	Command* cont_LEFT_STICK_DOWN;

	Command* cont_RIGHT_STICK_LEFT;
	Command* cont_RIGHT_STICK_RIGHT;
	Command* cont_RIGHT_STICK_UP;
	Command* cont_RIGHT_STICK_DOWN;
};

#endif // !INPUTHANDLER_H


