/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description	...
*/

#include "Engine.h"
#include "PlayableCharacter.h"

void Engine::update(float dtAsSeconds) {

	if (m_GameState == GameState::MAIN_MENU) {
		m_MainView.reset(
			sf::FloatRect(0, 0, resolution.x, resolution.y));
		
		// Handle Animated Background
		if(m_animatedBackgroundFrame >= m_animatedBackgroundMaxFrames) {
			m_animatedBackgroundFrame = 0;
		}

		//This code will read in the folder that has the images to make the start video.
		m_animatedBackgroundImage.loadFromFile(
			std::string("graphics/Menu_Video/Menu/Menu ")
			.append(std::to_string(m_animatedBackgroundFrame++))
			.append(".png"));

		//Sets the images to be drawn to the background. 
		m_MenuBackgroundTexture.loadFromImage(m_animatedBackgroundImage);
		m_MenuBackgroundSprite.setTexture(m_MenuBackgroundTexture);

		//	Handle Buttons
		while (m_Window.pollEvent(m_event)) {
			for (std::list<GUI::Button>::iterator it = m_mainMenuButtons.begin(); it != m_mainMenuButtons.end(); ++it) {
				it->update(m_event, m_GameTimeTotal, m_Window);
			}
		}
	}
	else if (m_GameState == GameState::LEVEL_SELECT) {
		//	Handle Buttons
		while (m_Window.pollEvent(m_event)) {
			for (std::list<GUI::Button>::iterator it = m_levelSelectButtons.begin(); it != m_levelSelectButtons.end(); ++it) {
				it->update(m_event, m_GameTimeTotal, m_Window);
			}
		}
	}
	else if (m_GameState == GameState::LOADING) {
		// Load a Level
		loadLevel();

		m_GameState = GameState::READYUP;
	}
	else if (m_GameState == GameState::READYUP) {
		// Put Paused Screen Update code here
	}
	else if (m_GameState == GameState::PLAYING) {
		//	Assign the active controller
		while (m_Window.pollEvent(m_event)) { //	<--	Needed for input to function
			
		}

		//Update Switches		
		for (std::list<ToggleSwitch*>::iterator switchIt = m_SwitchList.begin();
			switchIt != m_SwitchList.end(); switchIt++) {

			(*switchIt)->update(m_GameTimeTotal, m_ArrayLevel);
			if (m_Player.getSprite().getGlobalBounds().intersects(
				(*switchIt)->getSprite().getGlobalBounds())) {
				if ((*switchIt)->toggle(m_GameTimeTotal,m_SM)) {
					doorUpdate(dtAsSeconds, (*switchIt));
				}
			}
		}

		//update Items
		for (std::list<Item*>::iterator itemIter = m_ItemList.begin();
			itemIter != m_ItemList.end();) {

			//update Item
			(*itemIter)->update(dtAsSeconds, m_ArrayLevel);

			//Pick up Item
			if (m_Player.getSprite().getGlobalBounds().intersects(
				(*itemIter)->getSprite().getGlobalBounds())) {
				m_Player.chargeFromPickup((*itemIter)->getCapacity(),m_SM);
				delete* itemIter;
				itemIter = m_ItemList.erase(itemIter++);
			}
			else {
				itemIter++;
			}
		}

		//Update Lasers
		for (std::list<LaserPointer*>::iterator lasIt = m_LaserPointerList.begin();
			lasIt != m_LaserPointerList.end();lasIt++) {
			(*lasIt)->update(m_GameTimeTotal,m_SM);
			//is the laser Active
			if ((*lasIt)->isActive()) {
				//If so is the player touching it
				if ((*lasIt)->getLaser().getGlobalBounds().intersects(m_Player.getPosition())) {
					m_GameState = GameState::ENDGAME;
				}
			}
		}

		// Update Player
		m_Player.update(dtAsSeconds, m_ArrayLevel);

		if (m_Player.isTargeting())
		{
			//std::cout << "\nUpdating targeting";
			m_Player.updateTargeting();
		}

		//Handle-Update bullets
		if ((m_GameTimeTotal.asMilliseconds()
			- m_SinceLastShot.asMilliseconds() > 500) &&
			(m_Player.getChargeLevel() > m_Player.getShotCost())) {

			if (m_Player.isShooting()) {
				//Choose bullet spawn dependant on current Animation
				if (m_Player.getDir() == PlayableCharacter::Direction::IDLE) {
					bullets[currentBullet].shoot(
						m_Player.getCenter().x - 10, m_Player.getCenter().y - 25,
						m_Player.getTarget().x, m_Player.getTarget().y);
				}
				else if (m_Player.getDir() == PlayableCharacter::Direction::RIGHT) {
					bullets[currentBullet].shoot(
						m_Player.getCenter().x - 10, m_Player.getCenter().y - 25,
						m_Player.getTarget().x, m_Player.getTarget().y);
				}
				else if (m_Player.getDir() == PlayableCharacter::Direction::LEFT) {
					bullets[currentBullet].shoot(
						m_Player.getCenter().x - 40, m_Player.getCenter().y - 25,
						m_Player.getTarget().x, m_Player.getTarget().y);
				}
				else {
					bullets[currentBullet].shoot(
						m_Player.getCenter().x - 10, m_Player.getCenter().y - 25,
						m_Player.getTarget().x, m_Player.getTarget().y);
				}
				
				bullets[currentBullet].setShotPower(11);
				m_SM.playPlayerShoot();
				currentBullet++;
				m_Player.playerShot(false);
				m_SinceLastShot = m_GameTimeTotal;
				
				if (currentBullet > 4) {
					currentBullet = 0;
				}
			}
		}

		m_Hud.setGunCharge(m_Player.getChargeLevel());
		
		for (int i = 0; i < 5; i++) {
			if (bullets[i].isInFlight()) {
				bullets[i].update(dtAsSeconds);
				int bulletX = ((int)bullets[i].getCenter().x / TILE_SIZE);
				int bulletY = ((int)bullets[i].getCenter().y / TILE_SIZE);
				if (bulletX < 0) {
					bulletX = 0;
				}
				if (bulletX > m_LM.getLevelSize().x) {
					bulletX = m_LM.getLevelSize().x;
				}
				if (bulletY < 0) {
					bulletY = 0;
				}
				if (bulletY > m_LM.getLevelSize().y) {
					bulletY = m_LM.getLevelSize().y;
				}
				if ((m_ArrayLevel[bulletY][bulletX] == 1) || (m_ArrayLevel[bulletY][bulletX] == 2) ||
					(m_ArrayLevel[bulletY][bulletX] == 3) || (m_ArrayLevel[bulletY][bulletX] == 5)) {
					bullets[i].stop(m_SM);
				}
			}
		}

		//update Enemy
		for (std::list<Enemy*>::iterator it = m_EnemyList.begin(); it != m_EnemyList.end(); it++) {
			(*it)->update(dtAsSeconds, m_ArrayLevel);

			//check for bullet Collision
			for (int i = 0; i < 5; i++) {
				if (bullets[i].isInFlight()) {
					if (bullets[i].getSprite().getGlobalBounds().intersects
					((*it)->getSprite().getGlobalBounds())) {

						bullets[i].stop(m_SM);
						(*it)->takeDamage(bullets[i].getShotPower());
					}
				}
			}

			//check for player or Dead Enemy
			if ((*it)->getCone().getLocalBounds().intersects(m_Player.getPosition())) {
				//check if enemy detection Event happened in the last second
				if (m_GameTimeTotal.asMilliseconds()
					- (*it)->getlastdetectTime() > 500) {

					(*it)->increaseAwarenessLevel(m_Player.getCenter(),
						m_Player.getDetectLevel(),m_GameTimeTotal,m_SM);

					if ((*it)->getAwareness() >= 100.0) {
						m_GameState = GameState::ENDGAME;
					}
				}
			}
			else if ((*it)->getAwareness() >= 0) {
				//check if enemy detection Event happened in the last half second
				if (m_GameTimeTotal.asMilliseconds()
					- (*it)->getlastdetectTime() > 500) {

					//reduce Enemies detectionLevel
					(*it)->reduceAwareness(m_GameTimeTotal);
				}
			}

			for (std::list<Enemy*>::iterator checkDeathIter = m_EnemyList.begin();
				checkDeathIter != m_EnemyList.end(); checkDeathIter++) {

				if ((*it)->getCone().getLocalBounds().intersects((*checkDeathIter)->getPosition()))	{
					if (!(*checkDeathIter)->isConscious()) {
						
						(*it)->increaseAwarenessLevel((*checkDeathIter)->getCenter(), m_Player.getDetectLevel(),
							m_GameTimeTotal,m_SM);
					}
				}
			}
		}

		//update Cameras
		for (std::list<Camera*>::iterator cameraIt = m_CameraList.begin();
			cameraIt != m_CameraList.end();cameraIt++) {

			(*cameraIt)->update(dtAsSeconds, m_ArrayLevel);

			//check for bulletCollision
			for (int i = 0;i < 5;i++) {
				if (bullets[i].isInFlight()) {
					if (bullets[i].getSprite().getGlobalBounds().intersects
					((*cameraIt)->getSprite().getGlobalBounds())) {

						bullets[i].stop(m_SM);
						(*cameraIt)->takeDamage();
					}
				}
			}

			//check for player
			if ((*cameraIt)->getCone().getGlobalBounds().
				intersects(m_Player.getPosition())) {
				if (m_GameTimeTotal.asMilliseconds() - (*cameraIt)->getlastdetectTime() > 500) {
					
					//increase awareness
					(*cameraIt)->increaseAwarenessLevel(m_Player.getCenter(),
					m_Player.getDetectLevel(), m_GameTimeTotal,m_SM);
					
					//is player detetced
					if ((*cameraIt)->getAwareness() >= 100) {
						m_GameState = GameState::ENDGAME;
					}
				}
			}
			//Decrease awareness Level
			else if ((*cameraIt)->getAwareness() >= 0) {
				if (m_GameTimeTotal.asMilliseconds()
					- (*cameraIt)->getlastdetectTime() > 500) {
					(*cameraIt)->reduceAwareness(m_GameTimeTotal);
				}
			}

			//check for Dead Ally
			for (std::list<Enemy*>::iterator checkDeathOnCamIter = m_EnemyList.begin();
				checkDeathOnCamIter != m_EnemyList.end();checkDeathOnCamIter++) {

				//is camera visionCone intersecting Enemy sprite
				if((*checkDeathOnCamIter)->getCone().getLocalBounds().
					intersects((*checkDeathOnCamIter)->getPosition())) {

					//if Enemy is unconcious..... "CONCERN!!!!"
					if (!(*checkDeathOnCamIter)->isConscious()) {

						(*checkDeathOnCamIter)->increaseAwarenessLevel(
							(*checkDeathOnCamIter)->getCenter(), m_Player.getDetectLevel(),
							m_GameTimeTotal, m_SM
						);
					}
				}
			}
		}

		// Detect collisions and see if characters have reached the goal tile
		// The second part of the if condition is only executed
		// when player is touching the home tile
		if (detectCollisions(m_Player)) {
			// New level required
			m_GameState = GameState::MAIN_MENU;

			// Play the reach goal sound
			m_SM.playReachGoal();

		}

		// Centre full screen around character
		m_MainView.setCenter(m_Player.getCenter());
		m_MiniMap.setCenter(m_Player.getCenter());

		// Time to update the HUD?
		// Increment the number of frames since the last HUD calculation
		m_FramesSinceLastHUDUpdate++;

		// Update the HUD every m_TargetFramesPerHUDUpdate frames
		if (m_FramesSinceLastHUDUpdate > m_TargetFramesPerHUDUpdate) {
			std::cout << "\nUpdating HUD";
			// Update game HUD text
			std::stringstream ssTime;
			std::stringstream ssLevel;

			// Update the time text
			ssTime << int(m_TimeRemaining);
			m_Hud.setTime(ssTime.str());
			
			m_Hud.setHidden(m_Player.getHudDetectLevel());
			m_Hud.setGunCharge(100);
			m_FramesSinceLastHUDUpdate = 0;
		}

		//update Muse positioning
		mouseScreenPosition = sf::Mouse::getPosition();

		// Convert mouse position to world coordinates of mainView
		mouseWorldPosition = m_Window.mapPixelToCoords(
			sf::Mouse::getPosition(), m_MainView);
	}
	else if (m_GameState == GameState::PAUSED) {
		// Put Loading Screen Update code here

	}
	else if (m_GameState == GameState::SETTINGS) {
		// Put Settings Screen Update code here

		//	Handle Buttons
		//	List all Settings Pages
		if (m_SettingsPage == SettingsPage::LIST) {
			while (m_Window.pollEvent(m_event)) {
				for (std::list<GUI::Button>::iterator it = m_settingsButtons.begin(); it != m_settingsButtons.end(); ++it) {
					it->update(m_event, m_GameTimeTotal, m_Window);
				}
			}
		}
		else if (m_SettingsPage == SettingsPage::GRAPHICS) {
			while (m_Window.pollEvent(m_event)) {
				for (std::list<GUI::Button>::iterator it = m_graphicsSettingsButtons.begin(); it != m_graphicsSettingsButtons.end(); ++it) {
					it->update(m_event, m_GameTimeTotal, m_Window);
				}
			}
		}
		else if (m_SettingsPage == SettingsPage::AUDIO) {
			while (m_Window.pollEvent(m_event)) {
				for (std::list<GUI::Button>::iterator it = m_audioSettingsButtons.begin(); it != m_audioSettingsButtons.end(); ++it) {
					it->update(m_event, m_GameTimeTotal, m_Window);
				}
			}
		}
		else if (m_SettingsPage == SettingsPage::GAMEPLAY) {
			while (m_Window.pollEvent(m_event)) {
				for (std::list<GUI::Button>::iterator it = m_gameplaySettingsButtons.begin(); it != m_gameplaySettingsButtons.end(); ++it) {
					it->update(m_event, m_GameTimeTotal, m_Window);
				}
			}
		}	
	}
	else if (m_GameState == GameState::ENDGAME) {

	m_MainView.reset(
		sf::FloatRect(0, 0, 1910, 1081));

	// Handle Animated Background for the EndGame
	if (m_endAnimatedBackgroundFrame >= m_endAnimatedBackgroundMaxFrames) {
		m_GameState = GameState::MAIN_MENU;
		m_endAnimatedBackgroundFrame = 38;
	}

	//This code will read in the folder that has the images to make the EndCredits.
	m_endAnimatedBackgroundImage.loadFromFile(
		std::string("graphics/Menu_Video/EndCredits/EndCredits ")
		.append(std::to_string(m_endAnimatedBackgroundFrame++))
		.append(".png"));

	//Sets the images to be drawn to the background for the endgame. 
	m_EndBackgroundTexture.loadFromImage(m_endAnimatedBackgroundImage);
	m_EndBackgroundSprite.setTexture(m_EndBackgroundTexture);
	}
}

/**
*	Cycles through the door List and Finds which one is closest to the referenced
*	Switch object, The closest one is always the connected Door
*/
void Engine::doorUpdate(float dtAsSeconds, ToggleSwitch *Switch) {
	//update Doors
	double currentShortest = std::numeric_limits<double>::infinity();
	Door* shortest = NULL;

	for (std::list<Door*>::iterator doorIt = m_DoorList.begin(); 
			doorIt != m_DoorList.end(); doorIt++) {

		if ((calcDistance((*doorIt)->getCenter(), (*Switch).getCenter()) < currentShortest)
			&& (*doorIt)->getDoorState()) {

			currentShortest = calcDistance((*doorIt)->getCenter(), (*Switch).getCenter());
			shortest = (*doorIt);
		}
	}

	shortest->doorState();
	shortest->update(dtAsSeconds, m_ArrayLevel);
}
