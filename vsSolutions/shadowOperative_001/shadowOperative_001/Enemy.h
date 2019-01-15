/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
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
	enum patrolDir { patrolLeft, patrolRight };
	patrolDir move = patrolLeft;
	friend patrolDir& operator++(patrolDir& mv, int incr);
	int sincePatrolAlter = 0;
	int sightAngle = 60;
	int detectionDistance1 = 50, detectionDistance2 = 100, detectionDistance3 = 150;
public:
	void update(float elapsedTIme,int** m_ArrayLevel);
	void spawn(sf::Vector2i startPosition, float gravity);
	void alterPatrol(bool patrol);
	sf::FloatRect getPosition();
	bool detectPlayer();
};

#endif // !ENEMY_H

