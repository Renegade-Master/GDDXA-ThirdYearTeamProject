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

class Enemy : public PlayableCharacter
{
private:
	sf::Vector2f m_SpawnPosition;
	bool patrolValid;
	// This is a pure virtual function
	bool handleInput();
public:
	void update(char** m_ArrayLevel);
	void spawn(sf::Vector2f startPosition, float gravity);
};

#endif // !ENEMY_H

