/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description
*/

#include "Engine.h"

Engine::Engine() {
	// Get the screen resolution and create an SFML window and View
	sf::Vector2f resolution;
	//resolution.x = sf::VideoMode::getDesktopMode().width;
	//resolution.y = sf::VideoMode::getDesktopMode().height;
	resolution.x = 1280;
	resolution.y = 720;

	m_Window.create(sf::VideoMode(resolution.x, resolution.y),
		"Thomas was late",
		sf::Style::Default);

	// Initialize the full screen view
	m_MainView.setSize(resolution);
	m_HudView.reset(
		sf::FloatRect(0, 0, resolution.x, resolution.y));


	// Can this graphics card use shaders?
	if (!sf::Shader::isAvailable())	{
		// Time to get a new PC
		m_Window.close();
	}
	else {
		// Load two shaders (1 vertex, 1 fragment)
		m_RippleShader.loadFromFile("shaders/vertShader.vert",
			"shaders/rippleShader.frag");
	}


	m_BackgroundTexture = TextureHolder::GetTexture(
		"graphics/background.png");

	// Associate the sprite with the texture
	m_BackgroundSprite.setTexture(m_BackgroundTexture);

	// Load the texture for the background vertex array
	m_TextureTiles = TextureHolder::GetTexture(
		"graphics/tiles_sheet.png");

	// Initialize the particle system
	m_PS.init(1000);
}

void Engine::run() {
	// Timing 	
	sf::Clock clock;

	while (m_Window.isOpen()) {
		sf::Time dt = clock.restart();
		// Update the total game time
		m_GameTimeTotal += dt;
		// Make a decimal fraction from the delta time
		float dtAsSeconds = dt.asSeconds();

		input();
		update(dtAsSeconds);
		draw();
	}
}
void Engine::enemySpawn()
{
	int numOfEnemies = m_LM.getNumOfEnemies();
	for (int i = 0;i < numOfEnemies;i++)
	{
		//Enemy.push_back(createEnemy(m_LM.getEnemyPosition(),GRAVITY));
	}
}
