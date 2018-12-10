#pragma once
#ifndef ENEMY_H
#define ENEMY_H
#include "PlayableCharacter.h"

class Enemy : public PlayableCharacter
{
private:
	sf::Vector2f m_SpawnPosition;
	bool patrolValid;
public:
	void update(char** m_ArrayLevel);
	void spawn(sf::Vector2f startPosition, float gravity);
};
ff
#endif // !ENEMY_H

