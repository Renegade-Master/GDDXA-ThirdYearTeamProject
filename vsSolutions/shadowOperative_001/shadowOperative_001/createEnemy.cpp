/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2018/12/11	YYYY/MM/DD
*	@description	Create a new Enemy Object
*/

#include "Engine.h"

/**
*	Create a new enemy.
*/
Enemy* createEnemy(sf::Vector2i position,float Gravity,sf::Time gameStart) {
	Enemy* enemy = new Enemy();
	enemy->spawn(position, Gravity,gameStart);
	//std::cout << "\ncreated Enemy";
	return(enemy);
}