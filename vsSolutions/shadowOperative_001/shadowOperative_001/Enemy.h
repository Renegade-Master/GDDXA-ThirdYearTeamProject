/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description
*/

#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include "PlayableCharacter.h"

class Enemy : public PlayableCharacter {
private:
	sf::Vector2i m_SpawnPosition;
	bool patrolValid;
	// This is a pure virtual function
	virtual bool handleInput();

public:
	void update(float elapsedTIme);
	void spawn(sf::Vector2i startPosition, float gravity);
};

#endif // !ENEMY_H

