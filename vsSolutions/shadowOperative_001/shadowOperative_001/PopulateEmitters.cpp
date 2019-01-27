/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description
*/

#include "Engine.h"

/**
*
*/
void Engine::populateEmitters(std::vector <sf::Vector2f>& vSoundEmitters, int** arrayLevel) {
	// Make sure the vector is empty
	vSoundEmitters.empty();

	// Keep track of the previous emitter
	// so we don't make too many
	sf::FloatRect previousEmitter;

	// Search for fire in the level
	for (int x = 0; x < (int)m_LM.getLevelSize().x; x++) {
		for (int y = 0; y < (int)m_LM.getLevelSize().y; y++) {
			if (arrayLevel[y][x] == 2) {// fire is present
				// Skip over any fire tiles too 
				// near a previous emitter
				if (!sf::FloatRect(x * TILE_SIZE,
					y * TILE_SIZE,
					TILE_SIZE,
					TILE_SIZE).intersects(previousEmitter)){
					// Add the coordiantes of this water block
					vSoundEmitters.push_back(
						sf::Vector2f(x * TILE_SIZE, y * TILE_SIZE));

					// Make a rectangle 6 blocks x 6 blocks,
					// so we don't make any more emitters 
					// too close to this one
					previousEmitter.left = x * TILE_SIZE;
					previousEmitter.top = y * TILE_SIZE;
					previousEmitter.width = TILE_SIZE * 6;
					previousEmitter.height = TILE_SIZE * 6;
				}
			}
		}
	}
	return;
}