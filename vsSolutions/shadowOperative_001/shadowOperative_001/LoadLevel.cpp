/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description
*/

#include "Engine.h"

/**
*	Load the Next Level of the game by reading in the map and instantiating objects
*/
void Engine::loadLevel() {
	if (m_GameState == GameState::LOADING) {
		// Delete the previously allocated memory
		for (int i = 0; i < m_LM.getLevelSize().y; ++i) {
			delete[] m_ArrayLevel[i];

		}

		delete[] m_ArrayLevel;
		m_CameraList.clear();
		m_DoorList.clear();
		m_EnemyList.clear();
		m_ItemList.clear();
		m_LaserPointerList.clear();
		m_SwitchList.clear();


		// Load the next 2d array with the map for the level
		// And repopulate the vertex array as well
		m_ArrayLevel = m_LM.nextLevel(m_VALevel);

		// Spawn Player and Enemies
		m_Player.spawn(m_LM.getStartPosition(), GRAVITY);
		enemySpawn();

		//Spawn Items
		if (m_LM.getNumOfItems() >= 1) {
			ItemSpawn();
		}
		//Spawn Doors
		if (m_LM.getNumOfDoors() >= 1) {
			doorSpawn();
		}
		//Spawn switches
		if (m_LM.getNumSwitches() >= 1) {
			spawnSwitches();
		}
		//Spawn LaserPointer
		if (m_LM.getNumLaserPointers() >= 1) {
			spawnLasers();
		}
		//	Spawn Cameras
		if (m_LM.getNumCams() >= 1) {
			spawnCamera();
		}

		m_GameState = GameState::READYUP;
	}
}