/**
*	@author			Ciaran Bent [K00221230]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description
*/

#pragma once
#ifndef BOB_H
#define BOB_H

#include "PlayableCharacter.h"

class Bob : public PlayableCharacter {
public:
	// A constructor specific to Bob
	Bob();		// Was Bob::Bob() but that wasn't working

	// The overriden input handler for Bob
	bool virtual handleInput();

};
#endif // !BOB_H