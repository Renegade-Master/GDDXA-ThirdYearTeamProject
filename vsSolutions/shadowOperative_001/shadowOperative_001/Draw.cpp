/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description
*/

#include "Engine.h"

void Engine::draw() {
	// Rub out the last frame
	m_Window.clear(sf::Color::White);

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

	// Draw the particle system
	if (m_PS.running())	{
		m_Window.draw(m_PS);
	}

	// Draw the HUD
	// Switch to m_HudView
	m_Window.setView(m_HudView);
	m_Window.draw(m_Hud.getLevel());
	m_Window.draw(m_Hud.getTime());
	if (!m_Playing)	{
		m_Window.draw(m_Hud.getMessage());
	}

	// Show everything we have just drawn
	m_Window.display();
}