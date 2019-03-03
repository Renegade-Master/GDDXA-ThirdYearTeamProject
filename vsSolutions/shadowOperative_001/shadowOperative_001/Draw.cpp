/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description
*/

#include "Engine.h"

/**
*	Draw all sprites to the screen.
*/
void Engine::draw() {
	//	Fill the Window to clear the last frame
	m_Window.clear(sf::Color::Black);

	if (m_GameState == GameState::MAIN_MENU) {
		// Switch to m_MainView
		m_Window.setView(m_MainView);

		// Draw the background, complete with shader effect for the Menu
		m_Window.draw(m_MenuBackgroundSprite);

		for (std::list<GUI::Button>::iterator it = m_mainMenuButtons.begin(); it != m_mainMenuButtons.end(); ++it) {
			m_Window.draw(*it);
		}
	}
	else if (m_GameState == GameState::LEVEL_SELECT) {
		// Switch to m_MainView
		m_Window.setView(m_MainView);

		m_Window.draw(m_BackgroundSprite);

		for (std::list<GUI::Button>::iterator it = m_levelSelectButtons.begin(); it != m_levelSelectButtons.end(); ++it) {
			m_Window.draw(*it);
		}
	}
	else if (m_GameState == GameState::LOADING) {
		// Put Loading Screen draw code here
	}
	else if (m_GameState == GameState::READYUP) {
		//Background of paused menu
		m_Window.draw(m_BackgroundSprite);

		//Message for the paused Game state
		m_Window.draw(m_Hud.getMessage());

	}
	else if (m_GameState == GameState::PLAYING) {
		/***---------------------***\
		|  HANDLE DRAWING WINDOW	|
		\***---------------------***/

		// Switch to background view
		m_Window.setView(m_BGMainView);

		// Draw the background, complete with shader effect
		m_Window.draw(m_BackgroundSprite);

		// Switch to m_MainView
		m_Window.setView(m_MainView);

		// Draw the Level
		m_Window.draw(m_VALevel, &m_TextureTiles);
		
		//Draw the Switches
		for (std::list<ToggleSwitch*>::iterator SwitchIt = m_SwitchList.begin();
			SwitchIt != m_SwitchList.end(); SwitchIt++) {

			m_Window.draw((*SwitchIt)->getSprite());
		}
		//Draw the doors
		for (std::list<Door*>::iterator doorIt = m_DoorList.begin();
			doorIt != m_DoorList.end();doorIt++) {
			m_Window.draw((*doorIt)->getDoorSprite());
		}

		//Draw Camera
		std::list<Camera*>::iterator cameraIt = m_CameraList.begin();
		for (;cameraIt != m_CameraList.end();cameraIt++) {
			m_Window.draw((*cameraIt)->getSprite());
			m_Window.draw((*cameraIt)->getDetectMeter());
		}
		//Draw Laserpointer
		for (std::list<LaserPointer*>::iterator LaserPointeriter = m_LaserPointerList.begin();
			LaserPointeriter != m_LaserPointerList.end();LaserPointeriter++) {
			m_Window.draw((*LaserPointeriter)->getSprite());
			if ((*LaserPointeriter)->isActive()){
				m_Window.draw((*LaserPointeriter)->getLaser());
			}
		}
		

		// Draw Player
		m_Window.draw(m_Player.getSprite());

		//drawing targeting laser
		if (m_Player.isTargeting()) {
			m_Window.draw(m_Player.getlaser());
		}

		//Draw Enemies
		if (!m_EnemyList.empty()) {
			for (std::list<Enemy*>::iterator it = m_EnemyList.begin();
				it != m_EnemyList.end(); it++) {
				m_Window.draw((*it)->getSprite());
				m_Window.draw((*it)->getDetectMeter());
			}
		}

		//Draw the bullets
		for (int i = 0; i < 5; i++) {
			if (bullets[i].isInFlight()) {
				m_Window.draw(bullets[i].getSprite());
			}
		}
		//Draw Items 
		for (std::list<Item*>::iterator itemIter = m_ItemList.begin();
			itemIter != m_ItemList.end(); itemIter++) {
			m_Window.draw((*itemIter)->getSprite());
		}

		/***---------------------***\
		|	  HANDLE DRAWING HUD	|
		\***---------------------***/
		
		// Switch to m_HudView
		m_Window.setView(m_HudView);
		m_Window.draw(m_Hud.getHidden());
		m_Window.draw(m_Hud.getGunBackground());
		m_Window.draw(m_Hud.getGunCharge());
		
		/***---------------------***\
		|  HANDLE DRAWING MINI_MAP	|
		\***---------------------***/
		
		m_Window.setView(m_BGMiniMap);
		m_Window.draw(m_BackgroundSprite);
		m_Window.setView(m_MiniMap);
		m_Window.draw(m_VALevel, &m_TextureTiles);
		m_Window.draw(m_Player.getSprite());
		
		//Draw the doors
		for (std::list<Door*>::iterator doorIt = m_DoorList.begin();
			doorIt != m_DoorList.end();doorIt++) {
			m_Window.draw((*doorIt)->getDoorSprite());
		}

		for (std::list<Enemy*>::iterator iter = m_EnemyList.begin();
			iter != m_EnemyList.end(); iter++) {

			m_Window.draw((*iter)->getSprite());
			m_Window.draw((*iter)->getCone());
		}
		
		for (std::list<Camera*>::iterator camIt = m_CameraList.begin();camIt != m_CameraList.end();camIt++) {
			m_Window.draw((*camIt)->getSprite());
			m_Window.draw((*camIt)->getCone());
		}
	}
	else if (m_GameState == GameState::PAUSED) {

	}
	else if (m_GameState == GameState::SETTINGS) {
		// Switch to m_MainView
		m_Window.setView(m_MainView);

		// Put Settings Screen draw code here
		m_Window.draw(m_BackgroundSprite);
		
		//	List all Settings Pages
		if (m_SettingsPage == SettingsPage::LIST) {			
			for (std::list<GUI::Button>::iterator it = m_settingsButtons.begin(); it != m_settingsButtons.end(); ++it) {
				m_Window.draw(*it);
			}			
		}
		//	List Graphics Settings
		else if (m_SettingsPage == SettingsPage::GRAPHICS) {			
			for (std::list<GUI::Button>::iterator it = m_graphicsSettingsButtons.begin(); it != m_graphicsSettingsButtons.end(); ++it) {
				m_Window.draw(*it);
			}			
		}
		//	List Audio Settings
		else if (m_SettingsPage == SettingsPage::AUDIO) {
			for (std::list<GUI::Button>::iterator it = m_audioSettingsButtons.begin(); it != m_audioSettingsButtons.end(); ++it) {
				m_Window.draw(*it);
			}
		}
		//	List Gameplay Settings
		else if (m_SettingsPage == SettingsPage::GAMEPLAY) {
			for (std::list<GUI::Button>::iterator it = m_gameplaySettingsButtons.begin(); it != m_gameplaySettingsButtons.end(); ++it) {
				m_Window.draw(*it);
			}
		}
	}
	else if (m_GameState == GameState::ENDGAME) {

		// Switch to m_MainView
		m_Window.setView(m_MainView);

		// Draw the endgame Credits.
		m_Window.draw(m_EndBackgroundSprite);

	}

	// Show everything we have just drawn
	m_Window.display();
}