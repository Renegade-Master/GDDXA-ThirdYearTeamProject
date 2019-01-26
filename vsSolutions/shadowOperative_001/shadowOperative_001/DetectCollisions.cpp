/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description	...
*/

#include "Engine.h"
#include "LevelManager.h"

bool Engine::detectCollisions(PlayableCharacter& character) {
	bool reachedGoal = false;
	// Make a rect for all his parts
	sf::FloatRect detectionZone = character.getPosition();

	// Make a FloatRect to test each block
	sf::FloatRect block;

	block.width = TILE_SIZE;
	block.height = TILE_SIZE;

	// Build a zone around thomas to detect collisions
	int startX = int(detectionZone.left / TILE_SIZE) - 1;
	int startY = int(detectionZone.top / TILE_SIZE) - 1;
	int endX = int(detectionZone.left / TILE_SIZE) + 2;

	// Player is quite tall so check a few tiles vertically
	int endY = int(detectionZone.top / TILE_SIZE) + 3;

	// Make sure we don't test positions lower than zero
	// Or higher than the end of the array
	if (startX < 0) {
		startX = 0;
	}
	if (startY < 0) {
		startY = 0;
	}
	if (endX >= m_LM.getLevelSize().x) {
		endX = m_LM.getLevelSize().x;
	}
	if (endY >= m_LM.getLevelSize().y) {
		endY = m_LM.getLevelSize().y;
	}

	// Has the character fallen out of the map?
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!This can be part of level manager!!!!!!!!!!!!!!!!!!!!!!!!
	sf::FloatRect level(0, 0, m_LM.getLevelSize().x * TILE_SIZE, m_LM.getLevelSize().y * TILE_SIZE);
	if (!character.getPosition().intersects(level))	{
		// respawn the character
		std::cout << "YOU DIED!" << std::endl;
		character.spawn(m_LM.getStartPosition(), GRAVITY);
		//this->Engine::m_GameState = Engine::m_GameState::MAIN_MENU;
	}
	
	//if Door is valid pass through
	doorValid = true;
	//if not then dont	
	for (std::list<Door*>::iterator collDetect = m_DoorList.begin();
			collDetect != m_DoorList.end();collDetect++) {

		if (character.getPosition().intersects((*collDetect)->getPosition())) {
			doorValid = (*collDetect)->getValidState();
		}
	}

	//	Is the Player capable of Hiding an Enemy?
	if (character.getClassName() == sf::String("Player")) {
		for (std::list<Enemy*>::iterator enem = m_EnemyList.begin();
			enem != m_EnemyList.end(); enem++) {

			if (!(*enem)->isConscious()) {
				if (character.getPosition().intersects((*enem)->getPosition())) {
					(*enem)->EnemyCrate();
				}
			}

		}
	}

	for (int x = startX; x < endX; x++)	{
		for (int y = startY; y < endY; y++) {
			// Initialize the starting position of the current block
			block.left = x * TILE_SIZE;
			block.top = y * TILE_SIZE;
			
			// Is character colliding with a regular block
			if (   (m_ArrayLevel[y][x] == 1)	|| (m_ArrayLevel[y][x] == 2)
				|| (m_ArrayLevel[y][x] == 3)	|| (m_ArrayLevel[y][x] == 4)
				|| (m_ArrayLevel[y][x] == 5)	|| (m_ArrayLevel[y][x] == 6)
				|| (m_ArrayLevel[y][x] == 7)	|| (m_ArrayLevel[y][x] == 8)
				|| (m_ArrayLevel[y][x] == 9)	|| (m_ArrayLevel[y][x] == 'j')
				|| (m_ArrayLevel[y][x] == 'k')	|| (m_ArrayLevel[y][x] == 'u')
				|| (!doorValid)) {

				if (character.getRight().intersects(block))	{
					character.stopRight(block.left);
				}
				else if (character.getLeft().intersects(block))	{
					character.stopLeft(block.left);
				}
				
				if (character.getFeet().intersects(block)) {
					character.stopFalling(block.top);
				}
				else if (character.getHead().intersects(block))	{
					character.stopJump();
				}
			}

			// If the Character is not touching any Collision blocks
			if (!character.getFeet().intersects(block)
				&& character.m_Action != PlayableCharacter::Action::JUMPING) {

				character.m_Action = PlayableCharacter::Action::FALLING;
			}
			else if (((character.m_Position.y - character.m_LastPosition.y)				// if (Y Change since last frame)
					> (character.m_LastPosition.y == (character.m_LastPosition.y += character.m_Gravity * 0.0167f)))) {	// less than (last Y + Gravity)

					character.m_Action = PlayableCharacter::Action::IDLE;
				}
			//}


			

			/*
			//// More collision detection here once we have learned about particle effects
			// Has the characters' feet touched fire or water?
			// If so, start a particle effect
			// Make sure this is the first time we have detected this
			// by seeing if an effect is already running			
			if (!m_PS.running()) {
				if (m_ArrayLevel[y][x] == 2 || m_ArrayLevel[y][x] == 3)	{
					if (character.getFeet().intersects(block)) {
						// position and start the particle system
						m_PS.emitParticles(character.getCenter());

					}
				}
			}
			*/

			// Has the character reached the goal?
			if (m_ArrayLevel[y][x] == 'Q') {
				// Character has reached the goal
				reachedGoal = true;
				this->Engine::m_GameState = Engine::GameState::MAIN_MENU;
			}
		}
	}

	// All done, return, whether or not a new level might be required
	return reachedGoal;
}