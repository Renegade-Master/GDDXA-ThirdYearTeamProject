/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description
*/

#include <iostream>

#include "Engine.h"

void Engine::draw() {
	// Rub out the last frame
	m_Window.clear(sf::Color::Black);

	if (GameState == State::MAIN_MENU) {
		// Switch to m_MainView
		m_Window.setView(m_MainView);

		for (std::list<GUI::Button>::iterator it = m_mainMenuButtons.begin(); it != m_mainMenuButtons.end(); ++it) {
			m_Window.draw(*it);
		}
	}
	else if (GameState == State::PLAYING) {
		// Update the shader parameters
		m_RippleShader.setUniform("uTime", m_GameTimeTotal.asSeconds());

		// Switch to background view
		m_Window.setView(m_BGMainView);
		// Draw the background
		//m_Window.draw(m_BackgroundSprite);

		// Draw the background, complete with shader effect
		m_Window.draw(m_BackgroundSprite, &m_RippleShader);

		// Switch to m_MainView
		m_Window.setView(m_MainView);

		// Draw the Level
		m_Window.draw(m_VALevel, &m_TextureTiles);



		// Draw thomas
		m_Window.draw(m_Thomas.getSprite());

		if (!m_EnemyList.empty())
		{
			//std::cout << "\nNumber of enemies:" << m_LM.getNumOfEnemies();
			for (std::list<Enemy*>::iterator it = m_EnemyList.begin(); it != m_EnemyList.end(); it++)
			{
				//std::cout << "\nDrawing enemies";
				m_Window.draw((*it)->getSprite());
			}
		}

		// Draw the particle system
		if (m_PS.running()) {
			m_Window.draw(m_PS);
		}

		// Draw the HUD
		// Switch to m_HudView
		m_Window.setView(m_HudView);
		m_Window.draw(m_Hud.getHidden());
		//m_Window.draw(m_Hud.getTime());
		m_Window.draw(m_Hud.getGunCharge());


		m_Window.setView(m_BGMiniMap);
		m_Window.draw(m_BackgroundSprite);
		m_Window.setView(m_MiniMap);
		m_Window.draw(m_VALevel, &m_TextureTiles);
		m_Window.draw(m_Thomas.getSprite());
		for (std::list<Enemy*>::iterator iter = m_EnemyList.begin();
			iter != m_EnemyList.end(); iter++)
		{
			m_Window.draw((*iter)->getSprite());
		}
	}
	else if (GameState == State::PAUSED) {
		m_Window.draw(m_Hud.getMessage());
	}
	else if (GameState == State::SETTINGS) {
		// Put Settings Screen draw code here
	}
	else if (GameState == State::LOADING) {
		// Put Loading Screen draw code here
	}

	// Show everything we have just drawn
	m_Window.display();
}