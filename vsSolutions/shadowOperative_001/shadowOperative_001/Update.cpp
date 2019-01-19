/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description
*/

#include <sstream>
#include <SFML/Graphics.hpp>
#include "Engine.h"
#include <iostream>
void Engine::update(float dtAsSeconds) {

	if (GameState == State::MAIN_MENU) {
		m_MainView.reset(
			sf::FloatRect(0, 0, resolution.x, resolution.y));
		int i = 0;
		for (std::list<GUI::Button>::iterator it = m_mainMenuButtons.begin(); it != m_mainMenuButtons.end(); ++it) {
			switch (i++) {
			case 0: // Enter Game
				if (it->getState() == GUI::State::clicked) {
					GameState = State::PAUSED;
				}
				break;
			case 1: // Settings
				if (it->getState() == GUI::State::clicked) {
					//GameState = State::SETTINGS;
				}
				break;
			case 2: // Quit
				if (it->getState() == GUI::State::clicked) {
					m_Window.close();
				}
				break;
			}
		}
	}
	else if (GameState == State::PLAYING) {
		if (m_NewLevelRequired) {
			// Load a Level
			loadLevel();
		}
		// Update Player
		m_Player.update(dtAsSeconds, m_ArrayLevel);


		//Handle-Update bullets
		std::cout << "\nGun Charge:" << m_Player.getChargeLevel();
		if ((m_GameTimeTotal.asMilliseconds()
			- m_SinceLastShot.asMilliseconds() > 100)&& 
			(m_Player.getChargeLevel()>m_Player.getShotCost()))
		{
			std::cout << "\nvalid shooting";
			if (m_Player.isShooting())
			{
				bullets[currentBullet].shoot(
					m_Player.getCenter().x, m_Player.getCenter().y,
					m_Player.getCenter().x + 10, m_Player.getCenter().y + 0.0001);
				/*std::cout << "\nm_Player.getCenter().x"<< m_Player.getCenter().x<<
					"\nm_Player.getCenter().y"<< m_Player.getCenter().y << 
					"\nm_Player.getCenter().x + 10 " << m_Player.getCenter().x+10 <<
					"\nm_Player.getCenter().y" << m_Player.getCenter().y +0.0001;*/
				currentBullet++;
				m_Player.playerShot(false);
				m_SinceLastShot = m_GameTimeTotal;
				if (currentBullet > 4)
				{
					currentBullet = 0;
				}
			}
		}
		for (int i = 0;i < 5;i++)
		{
			if (bullets[i].isInFlight())
			{
				//std::cout << "\nupdating bullets " <<i;
				bullets[i].update(dtAsSeconds);
				int bulletX = ((int)bullets[i].getCenter().x / TILE_SIZE);
				int bulletY = ((int)bullets[i].getCenter().y / TILE_SIZE);
				if (bulletX < 0)
				{
					bulletX = 0;
				}
				if (bulletX > m_LM.getLevelSize().x)
				{
					bulletX = m_LM.getLevelSize().x;
				}
				if (bulletY < 0)
				{
					bulletY = 0;
				}
				if (bulletY > m_LM.getLevelSize().y)
				{
					bulletY = m_LM.getLevelSize().y;
				}

				/*std::cout << "\nbulletX:" << bulletX;
				std::cout << "\nbulletY:" << bulletY;*/
				if ((m_ArrayLevel[bulletY][bulletX] == 1) || (m_ArrayLevel[bulletY][bulletX] == 2) ||
					(m_ArrayLevel[bulletY][bulletX] == 3) || (m_ArrayLevel[bulletY][bulletX] == 5))
				{
					//std::cout << "\nBullet hit wall";
					bullets[i].stop();
				}
			}
		}


		
		//update Enemy
		for (std::list<Enemy*>::iterator it = m_EnemyList.begin(); it != m_EnemyList.end(); it++)
		{
			(*it)->update(dtAsSeconds,m_ArrayLevel);
			//check for player
			if ((*it)->getCone().getLocalBounds().intersects(m_Player.getPosition()))
			{
				//check if enemy detection Event happened in the last second
				if (m_GameTimeTotal.asMilliseconds()
					- (*it)->getlastdetectTime() > 500)
				{
					(*it)->increaseAwarenessLevel(m_Player.getCenter(), m_Player.getDetectLevel(),m_GameTimeTotal);
					if ((*it)->getAwareness() <= 100.0)
					{
						std::cout << "\nDetected";
					}
					std::cout << "\n" << (*it)->getAwareness();
				}
			}
			else if ((*it)->getAwareness() >= 0)
			{
				//check if enemy detection Event happened in the last second
				if (m_GameTimeTotal.asMilliseconds()
					- (*it)->getlastdetectTime() > 500)
				{
					//reduce Enemies detectionLevel
					(*it)->reduceAwareness(m_GameTimeTotal);
				}
			}
		}

		// Detect collisions and see if characters have reached the goal tile
		// The second part of the if condition is only executed
		// when thomas is touching the home tile
		if (detectCollisions(m_Player)) {
			// New level required
			m_NewLevelRequired = true;

			// Play the reach goal sound
			m_SM.playReachGoal();

		}

		// Count down the time the player has left
		//m_TimeRemaining -= dtAsSeconds;

		// Have Player and Bob run out of time?
		if (m_TimeRemaining <= 0) {
			m_NewLevelRequired = true;
		}

		// Check if a fire sound needs to be played

		// Iterate through the vector of Vector2f objects
		for (std::vector<sf::Vector2f>::iterator it = m_FireEmitters.begin(); it != m_FireEmitters.end(); it++) {
			// Where is this emitter?
			// Store the location in pos
			float posX = (*it).x;
			float posY = (*it).y;

			// is the emiter near the player?
			// Make a 500 pixel rectangle around the emitter
			sf::FloatRect localRect(posX - 250, posY - 250, 500, 500);

			// Is the player inside localRect?
			if (m_Player.getPosition().intersects(localRect)) {
				// Play the sound and pass in the location as well
				m_SM.playFire(sf::Vector2f(posX, posY), m_Player.getCenter());
			}
		}

		// Centre full screen around appropriate character
		if (m_Character1)
		{
			m_MainView.setCenter(m_Player.getCenter());
			m_MiniMap.setCenter(m_Player.getCenter());
		}

		// Time to update the HUD?
		// Increment the number of frames since the last HUD calculation
		m_FramesSinceLastHUDUpdate++;

		// Update the HUD every m_TargetFramesPerHUDUpdate frames
		if (m_FramesSinceLastHUDUpdate > m_TargetFramesPerHUDUpdate) {
			// Update game HUD text
			std::stringstream ssTime;
			std::stringstream ssLevel;

			// Update the time text
			ssTime << (int)m_TimeRemaining;
			m_Hud.setTime(ssTime.str());
			
			// Update the level text
			m_Hud.setHidden(m_Player.getDetectLevel());
			
			
			//add call to player Gun later
			m_Hud.setGunCharge(100);
			m_FramesSinceLastHUDUpdate = 0;
		}

		// Update the particles
		if (m_PS.running()) {
			m_PS.update(dtAsSeconds);
		}
	}
	else if (GameState == State::PAUSED) {
		// Put Paused Screen Update code here
	}
	else if (GameState == State::SETTINGS) {
		// Put Settings Screen Update code here
	}
	else if (GameState == Engine::State::LOADING) {
		// Put Loading Screen Update code here
	}
}