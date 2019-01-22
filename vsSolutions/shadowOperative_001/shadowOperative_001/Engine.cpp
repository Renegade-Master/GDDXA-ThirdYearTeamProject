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

	int maxAnimations = 142;
	//Menu Background
	for (int images_in_animation = 1; images_in_animation < maxAnimations; images_in_animation++) {

		m_MenuBackgroundTexture = TextureHolder::GetTexture(
			"graphics/Menu_Video/Short_142_FirstVideo/Short_142 0.png");
	}

	// Associate the sprite with the texture for the Menu
	m_MenuBackgroundSprite.setTexture(m_MenuBackgroundTexture);

	/*
	sf::Texture m_myBackground;
	int maxAnimations = 142;

	for (int images_in_animation = 0; images_in_animation < maxAnimations; images_in_animation++) {
		m_myBackground.loadFromFile(std::string("graphics/Menu_Video/Short_142_FirstVideo/Short_142 ").append
		(std::to_string(images_in_animation)).append(".png"));
		m_MenuBackgroundSprite.setTexture(m_myBackground);
	}*/
	

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

void Engine::enemySpawn() {

	int numOfEnemies = m_LM.getNumOfEnemies();
	for (int i = 0;i < numOfEnemies;i++) {
		m_EnemyList.push_back(createEnemy(m_LM.getEnemyPosition(),GRAVITY,m_GameTimeTotal));
		//std::cout << "\nlist size" << m_EnemyList.size();
	}
}

//Spawns in the items into the game.
void Engine::ItemSpawn() {
		//m_ItemList.push_back(pItemList);
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

