/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description
*/

#include "Engine.h"

void Engine::loadLevel() {
	//m_Playing = false;
	GameState = State::LOADING;

	// Delete the previously allocated memory
	for (int i = 0; i < m_LM.getLevelSize().y; ++i)	{
		delete[] m_ArrayLevel[i];

	}
	delete[] m_ArrayLevel;

	// Load the next 2d array with the map for the level
	// And repopulate the vertex array as well
	m_ArrayLevel = m_LM.nextLevel(m_VALevel);

	// Prepare the sound emitters
	populateEmitters(m_FireEmitters, m_ArrayLevel);

	// How long is this new time limit
	m_TimeRemaining = m_LM.getTimeLimit();

	// Spawn Player and Bob
	m_Player.spawn(m_LM.getStartPosition(), GRAVITY);
	enemySpawn();
	//Spawn Items
	if (m_LM.getNumOfItems() >= 1){
		ItemSpawn();
	}
	//Spawn Doors
	if (m_LM.getNumOfDoors() >= 1) {
		doorSpawn();
	}
	if (m_LM.getNumSwitches() >= 1) {
		spawnSwitches();
	}

	// Make sure this code isn't run again
	m_NewLevelRequired = false;
	GameState = State::PLAYING;
}