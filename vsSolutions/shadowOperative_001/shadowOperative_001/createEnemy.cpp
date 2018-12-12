/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[]
*	@creationDate	2018/12/11	YYYY/MM/DD
*	@description	Create a new Enemy Object
*/


#include <iostream>
#include "Enemy.h"
#include "EnemyGenerator.h"

Enemy* createEnemy(sf::Vector2i position,float Gravity) {
	Enemy* enemy = new Enemy();
	enemy->spawn(position, Gravity);
	//std::cout << "\ncreated Enemy";
	return(enemy);
}