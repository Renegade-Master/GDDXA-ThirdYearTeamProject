#include "Enemy.h"
#include "EnemyGenerator.h"
#include<iostream>
Enemy* createEnemy(sf::Vector2i position,float Gravity)
{
	Enemy* enemy = new Enemy();
	enemy->spawn(position, Gravity);
	//std::cout << "\ncreated Enemy";
	return enemy;
}