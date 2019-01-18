/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description	...
*/

#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "PlayableCharacter.h"

class Player : public PlayableCharacter {
public:
	// A constructor specific to Player
	Player();		// Was Player::Player() but that wasn't working

	virtual void update(float elapsedTime, int** m_ArrayLevel);

	// The overriden input handler for Player
	virtual void PlayableCharacter::handleInput();

};
#endif // !PLAYER_H