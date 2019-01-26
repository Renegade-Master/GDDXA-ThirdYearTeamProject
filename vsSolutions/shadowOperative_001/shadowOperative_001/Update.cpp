/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description
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

		m_animatedBackgroundImage.loadFromFile(
			std::string("graphics/Menu_Video/Short_142_FirstVideo/Short_142 ")
			.append(std::to_string(m_animatedBackgroundFrame++))
			.append(".png"));

		m_MenuBackgroundTexture.loadFromImage(m_animatedBackgroundImage);
		m_MenuBackgroundSprite.setTexture(m_MenuBackgroundTexture);

		//	Handle Buttons
		while (m_Window.pollEvent(m_event)) {
			for (std::list<GUI::Button>::iterator it = m_mainMenuButtons.begin(); it != m_mainMenuButtons.end(); ++it) {
				it->update(m_event, m_GameTimeTotal, m_Window);
			}
		}
	}
	else if (m_GameState == GameState::PLAYING) {
		if (m_NewLevelRequired) {			
			// Load a Level
			m_GameState = GameState::LOADING;
			loadLevel();
		}

		//Update Switches		
		for (std::list<ToggleSwitch*>::iterator switchIt = m_SwitchList.begin(); 
				switchIt != m_SwitchList.end(); switchIt++) {
			
			(*switchIt)->update(m_GameTimeTotal, m_ArrayLevel);
			if (m_Player.getSprite().getGlobalBounds().intersects(
				(*switchIt)->getSprite().getGlobalBounds())) {
				if ((*switchIt)->toggle(m_GameTimeTotal)) {
					doorUpdate(dtAsSeconds, (*switchIt));
				}
			}
		}
		//update Items
		
		for (std::list<Item*>::iterator itemIter = m_ItemList.begin(); 
				itemIter != m_ItemList.end();) {
			
			//update Item
			(*itemIter)->update(dtAsSeconds,m_ArrayLevel);
			
			//Pick up Item
			if (m_Player.getSprite().getGlobalBounds().intersects(
				(*itemIter)->getSprite().getGlobalBounds())) {
				m_Player.chargeFromPickup((*itemIter)->getCapacity());
				delete *itemIter;
				itemIter = m_ItemList.erase(itemIter++);
				//(*itemIter)->~Item();
			}
			else {
				itemIter++;
			}
		}
		// Update Player
		m_Player.update(dtAsSeconds, m_ArrayLevel);
		
		if (m_Player.isTargeting())
		{
			//std::cout << "\nUpdating targeting";
			m_Player.updateTargeting(mouseWorldPosition);
		}
		//Handle-Update bullets
		//std::cout << "\nGun Charge:" << m_Player.getChargeLevel();
		if ((m_GameTimeTotal.asMilliseconds()
			- m_SinceLastShot.asMilliseconds() > 500) &&
			(m_Player.getChargeLevel() > m_Player.getShotCost()))
		{
			//std::cout << "\nvalid shooting";
			if (m_Player.isShooting())
			{
				//Choose bullet spawn dependant on current Animation
				if (m_Player.getDir() == PlayableCharacter::Direction::IDLE){
					bullets[currentBullet].shoot(
						m_Player.getCenter().x - 10, m_Player.getCenter().y - 25,
						mouseWorldPosition.x, mouseWorldPosition.y);
				}
				else if (m_Player.getDir() == PlayableCharacter::Direction::RIGHT){
					bullets[currentBullet].shoot(
						m_Player.getCenter().x - 10, m_Player.getCenter().y - 25,
						mouseWorldPosition.x, mouseWorldPosition.y);
				}
				else if (m_Player.getDir() == PlayableCharacter::Direction::LEFT){
					bullets[currentBullet].shoot(
						m_Player.getCenter().x - 40, m_Player.getCenter().y - 25,
						mouseWorldPosition.x, mouseWorldPosition.y);
				}
				else{
					bullets[currentBullet].shoot(
						m_Player.getCenter().x - 10, m_Player.getCenter().y - 25,
						mouseWorldPosition.x, mouseWorldPosition.y);
				}
				bullets[currentBullet].setShotPower(11);
				currentBullet++;
				m_Player.playerShot(false);
				m_SinceLastShot = m_GameTimeTotal;
				if (currentBullet > 4)
				{
					currentBullet = 0;
				}
			}
		}
		m_Hud.setGunCharge(m_Player.getChargeLevel());
		for (int i = 0;i < 5;i++)
		{
			if (bullets[i].isInFlight())
			{
				//std::cout << "\nupdating bullets " <<i;
				bullets[i].update(dtAsSeconds);
				int bulletX = ((int)bullets[i].getCenter().x / TILE_SIZE);
				int bulletY = ((int)bullets[i].getCenter().y / TILE_SIZE);
				if (bulletX < 0){
					bulletX = 0;
				}
				if (bulletX > m_LM.getLevelSize().x){
					bulletX = m_LM.getLevelSize().x;
				}
				if (bulletY < 0){
					bulletY = 0;
				}
				if (bulletY > m_LM.getLevelSize().y){
					bulletY = m_LM.getLevelSize().y;
				}
				/*std::cout << "\nbulletX:" << bulletX;
				std::cout << "\nbulletY:" << bulletY;*/
				if ((m_ArrayLevel[bulletY][bulletX] == 1) || (m_ArrayLevel[bulletY][bulletX] == 2) ||
					(m_ArrayLevel[bulletY][bulletX] == 3) || (m_ArrayLevel[bulletY][bulletX] == 5)){
					//std::cout << "\nBullet hit wall";
					bullets[i].stop();
				}
			}
		}

		
		//update Enemy
		for (std::list<Enemy*>::iterator it = m_EnemyList.begin(); it != m_EnemyList.end(); it++)
		{
			(*it)->update(dtAsSeconds, m_ArrayLevel);
			//check for bulletCollision
			for (int i = 0; i < 5; i++)
			{
				if (bullets[i].isInFlight())
				{
					if (bullets[i].getSprite().getGlobalBounds().intersects
					((*it)->getSprite().getGlobalBounds()))
					{
						std::cout << "\n Taking damage!!!!!!";
						bullets[i].stop();
						//(*it)->//LosesHealthDies
						(*it)->takeDamage(bullets[i].getShotPower());
						//(*it)->//is Enemy knoicked unconscious?
					}
				}
			}
			//check for player or Dead Enemy
			if ((*it)->getCone().getLocalBounds().intersects(m_Player.getPosition()))
			{
				//check if enemy detection Event happened in the last second
				if (m_GameTimeTotal.asMilliseconds()
					- (*it)->getlastdetectTime() > 500)
				{
					(*it)->increaseAwarenessLevel(m_Player.getCenter(), m_Player.getDetectLevel(), m_GameTimeTotal);
					if ((*it)->getAwareness() <= 100.0)
					{
						std::cout << "\nDetected";
					}
					std::cout << "\n" << (*it)->getAwareness();
				}
			}
			else if ((*it)->getAwareness() >= 0)
			{
				//check if enemy detection Event happened in the last half second
				if (m_GameTimeTotal.asMilliseconds()
					- (*it)->getlastdetectTime() > 500)
				{
					//reduce Enemies detectionLevel
					(*it)->reduceAwareness(m_GameTimeTotal);
				}
			}
			
			for (std::list<Enemy*>::iterator checkDeathIter = m_EnemyList.begin(); 
					checkDeathIter != m_EnemyList.end(); checkDeathIter++)
			{
				if ((*it)->getCone().getLocalBounds().intersects((*checkDeathIter)->getPosition()))
				{
					if (!(*checkDeathIter)->isConscious())
					{
						//std::cout << "\nEnemy Detecting Ally Death";
						(*it)->increaseAwarenessLevel((*checkDeathIter)->getCenter(), 1, m_GameTimeTotal);
					}
				}
			}
		}
		// Detect collisions and see if characters have reached the goal tile
		// The second part of the if condition is only executed
		// when player is touching the home tile
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

		// Centre full screen around character
		m_MainView.setCenter(m_Player.getCenter());
		m_MiniMap.setCenter(m_Player.getCenter());

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
			sf::Text isHidden = m_Hud.getHidden();
			m_Hud.setHidden(isHidden);
			//add call to player Gun later
			m_Hud.setGunCharge(100);
			m_FramesSinceLastHUDUpdate = 0;
		}

		// Update the particles
		if (m_PS.running()) {
			m_PS.update(dtAsSeconds);
		}

		//update Muse positioning
		mouseScreenPosition = sf::Mouse::getPosition();

		// Convert mouse position to world coordinates of mainView
		mouseWorldPosition = m_Window.mapPixelToCoords(
			sf::Mouse::getPosition(), m_MainView);
	}
	else if (m_GameState == GameState::PAUSED) {
		// Put Paused Screen Update code here
	}
	else if (m_GameState == GameState::LEVEL_SELECT) {
		//	Handle Buttons
		while (m_Window.pollEvent(m_event)) {
			for (std::list<GUI::Button>::iterator it = m_levelSelectButtons.begin(); it != m_levelSelectButtons.end(); ++it) {
				it->update(m_event, m_GameTimeTotal, m_Window);
			}
		}
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
	else if (m_GameState == GameState::LOADING) {
		// Put Loading Screen Update code here
	}
}
void Engine::doorUpdate(float dtAsSeconds, ToggleSwitch *Switch) {
	//update Doors
	//std::cout << "\nDoor update";	
	double currentShortest = std::numeric_limits<double>::infinity();
	Door* shortest = NULL;

	for (std::list<Door*>::iterator doorIt = m_DoorList.begin(); 
			doorIt != m_DoorList.end(); doorIt++) {
		//std::cout << "\nNext door";
		if ((calcDistance((*doorIt)->getCenter(), (*Switch).getCenter()) < currentShortest)
			&& (*doorIt)->getDoorState()) {

			currentShortest = calcDistance((*doorIt)->getCenter(), (*Switch).getCenter());
			shortest = (*doorIt);
			//std::cout << "\nnew Shortest";
		}
	}

	shortest->doorState();
	shortest->update(dtAsSeconds, m_ArrayLevel);
	//std::cout << "\nupdating Shortest";
}
double Engine::calcDistance(sf::Vector2f posOne, sf::Vector2f posTwo)  {
	double distance;
	double distancex = ((posOne.x - posTwo.x) * (posOne.x - posTwo.x));
	double distancey = ((posOne.y - posTwo.y) * (posOne.y - posTwo.y));

	return distance = sqrt(distancex - distancey);
}
