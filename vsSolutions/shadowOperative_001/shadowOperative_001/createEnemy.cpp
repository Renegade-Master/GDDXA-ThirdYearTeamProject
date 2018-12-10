#include "Enemy.h"
#include "EnemyGenerator.h"

Enemy* createEnemy(sf::Vector2f position,float Gravity)
{
	Enemy* enemy = new Enemy();
	enemy->spawn(position, Gravity);
	return enemy;
}