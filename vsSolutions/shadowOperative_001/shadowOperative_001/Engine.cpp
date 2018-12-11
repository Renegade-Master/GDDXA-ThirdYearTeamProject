/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description
*/

#include "Engine.h"
#include <iostream>
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
		m_EnemyList.push_back(createEnemy(m_LM.getEnemyPosition(),GRAVITY));
		std::cout << "\nlist size" << m_EnemyList.size();
	}

}
bool Engine::patrolStillValid(int** m_ArrayLevel, Enemy& character)
{
	// Make a rect for all his parts
	sf::FloatRect detectionZone = character.getPosition();

	// Make a FloatRect to test each block
	sf::FloatRect block;

	block.width = TILE_SIZE;
	block.height = TILE_SIZE;

	// Build a zone around thomas to detect collisions
	int startX = (int)(detectionZone.left / TILE_SIZE) - 1;
	int startY = (int)(detectionZone.top / TILE_SIZE) - 1;
	int endX = (int)(detectionZone.left / TILE_SIZE) + 2;

	// Thomas is quite tall so check a few tiles vertically
	int endY = (int)(detectionZone.top / TILE_SIZE) + 3;

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

	for (int x = startX; x < endX; x++) {
		for (int y = startY; y < endY; y++) {
			// Initialize the starting position of the current block
			block.left = x * TILE_SIZE;
			block.top = y * TILE_SIZE;

			//check the patrol loop
			if (m_ArrayLevel[y][x] == 'T')
			{
				if (character.getFeet().intersects(block))
				{
					std::cout << "\nFeet intersect Patrol Loop";
					return true;
				}
				else
				{
					std::cout << "\nFeet do not intersect Patrol Loop";
				}
			}
			else
			{
				std::cout << "\nFeet do not intersect Patrol Loop";
				return false;
			}
		}
	}
}
