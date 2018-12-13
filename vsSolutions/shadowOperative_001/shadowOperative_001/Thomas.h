/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description
*/

#pragma once
#ifndef THOMAS_H
#define THOMAS_H

#include "PlayableCharacter.h"

class Thomas : public PlayableCharacter {
public:
	// A constructor specific to Thomas
	Thomas();		// Was Thomas::Thomas() but that wasn't working

	virtual void update(float elapsedTime, int** m_ArrayLevel);

	// The overriden input handler for Thomas
	virtual bool handleInput();

};
#endif // !THOMAS_H