/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description
*/

#include "Engine.h"

Engine::Engine() {
	//resolution.x = sf::VideoMode::getDesktopMode().width;
	//resolution.y = sf::VideoMode::getDesktopMode().height;
	
	resolution.x = 1280;
	resolution.y = 720;

	m_Window.create(sf::VideoMode(resolution.x, resolution.y),
		"Shadow Operative",
		sf::Style::Default);
	m_Window.setFramerateLimit(60);

	// Initialize the full screen view
	m_MainView.setSize(resolution);
	m_HudView.reset(
		sf::FloatRect(0, 0, resolution.x, resolution.y));

	//MiniMap
	/*Set Minimap to be in the bottom left corner*/
	m_MiniMap.setSize(resolution.x / 20, resolution.y / 20);
	m_MiniMap.setViewport(sf::FloatRect(0.001f, 0.8f, 0.25f, 0.2f));
	m_BGMiniMap.setViewport(sf::FloatRect(0.001f, 0.8f, 0.25f, 0.2f));
	m_MiniMap.setRotation(180.f);
	m_BGMiniMap.setRotation(180.f);
	m_MiniMap.zoom(-30.00);

	// Can this graphics card use shaders?
	if (!sf::Shader::isAvailable())	{
		// Time to get a new PC
		m_Window.close();
	}
	else {
		// Load two shaders (1 vertex, 1 fragment)
		/*m_RippleShader.loadFromFile("shaders/vertShader.vert",
			"shaders/rippleShader.frag");*/
	}

	m_BackgroundTexture = TextureHolder::GetTexture(
		"graphics/background1-720.png");

	// Associate the sprite with the texture
	m_BackgroundSprite.setTexture(m_BackgroundTexture);

	//Menu Background
	m_MenuBackgroundTexture = TextureHolder::GetTexture(
		"graphics/MenuBackground.png");

	// Associate the sprite with the texture for the Menu
	m_MenuBackgroundSprite.setTexture(m_MenuBackgroundTexture);

	// Load the texture for the background vertex array
	m_TextureTiles = TextureHolder::GetTexture(
		"graphics/tileset_006.png");

	// Initialize the particle system
	m_PS.init(1000);

	// Initialise all the Buttons
	m_buttonFont.loadFromFile("fonts/Roboto-Light.ttf");
	initButtons();
	
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
/*
*	Use EnemyGenerator to create Enemies and spawn them on
*	Stored location variables
*/
void Engine::enemySpawn() {
	int numOfEnemies = m_LM.getNumOfEnemies();
	for (int i = 0;i < numOfEnemies;i++) {
		m_EnemyList.push_back(createEnemy(m_LM.getEnemyPosition(),
			GRAVITY,m_GameTimeTotal));
	}
}
//Spawns Items into the game.
void Engine::ItemSpawn() {
	//std::cout << "\n start";
	Item* newItem;
	int numOfItems = m_LM.getNumOfItems();
	//std::cout<<"\nThis is how many Items we Have:" << m_LM.getNumOfItems();
	for (int i = 0;i < numOfItems;i++){
		//std::cout << "\n Entering For Loop";
		char type = m_LM.getItemType();
		if (type == 'B') {
			//std::cout << "\n Should not be here";
			newItem = new gunBattery(m_LM.getItemPos());
		}
		m_ItemList.push_back(newItem);
	}
	std::cout << "\nItem Spawned";
}

/**
*	Is the Player using a controller?
*//*
bool Engine::getControls() {
	return(m_usingController);
}
*/


//bool Engine::getControls() {
//	return(m_usingController);
//}

