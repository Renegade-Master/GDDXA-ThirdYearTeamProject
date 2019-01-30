/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description
*/

#include "Engine.h"

/**
*	Default Constructor
*/
Engine::Engine() {
	resolution.x = 1280;
	resolution.y = 720;

	//	Initialise the Window with Default values
	refreshWindow();

	// Initialize the Main View
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

	//This is the background of the game.
	m_BackgroundTexture = TextureHolder::GetTexture(
		"graphics/background1-720.png");

	// Associate the Background Sprite with a Texture
	m_BackgroundSprite.setTexture(m_BackgroundTexture);

	// Load the texture for the background vertex array
	m_TextureTiles = TextureHolder::GetTexture(
		"graphics/tileset_008.png");

	// Initialise all the Buttons
	m_buttonFont.loadFromFile("fonts/Roboto-Light.ttf");
	
	//	Load up UI Buttons
	initButtons();	
}


/**
*	Execute the main game loop.
*/
void Engine::run() {
	// Timing 	
	sf::Clock clock;
	
	while (m_Window.isOpen()) {
		//std::cout << "GameState: " << int(this->m_GameState) << std::endl;
		dt = clock.restart();
	   	// Update the total game time
		m_GameTimeTotal += dt;
		// Make a decimal fraction from the delta time
		dtAsSeconds = dt.asSeconds();

		//	Main game cycle
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

/**
*	Spawns Items into the game
*/
void Engine::ItemSpawn() {
	//std::cout << "\n start";
	Item* newItem = nullptr;
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
*	Spawn Doors
*/
void Engine::doorSpawn() {
	int numDoors = m_LM.getNumOfDoors();
	for (int i = 0;i < numDoors;i++) {
		Door* door = new Door(m_LM.getDoorType(),m_LM.getDoorPos());
		m_DoorList.push_back(door);
	}
}

/**
*	Spawn Switches
*/
void Engine::spawnSwitches() {
	int numSwitches = m_LM.getNumSwitches();
	for (int i = 0;i < numSwitches;i++) {
		ToggleSwitch* togSwitch = new ToggleSwitch(m_GameTimeTotal,m_LM.getSwitchPos());
		m_SwitchList.push_back(togSwitch);
	}
}

/**
*	Spawn Cameras
*/
void Engine::spawnCamera() {
	int numCams = m_LM.getNumCams();
	for (int i = 0;i < numCams;i++) {
		Camera* camera = new Camera();
		camera->spawn(m_LM.getCamPos(), GRAVITY, m_GameTimeTotal, m_LM.getCamDir(),m_ArrayLevel);
		m_CameraList.push_back(camera);
	}
}

/**
*	Spawn Laserpointers
*/
void Engine::spawnLasers() {
	int numLas = m_LM.getNumLaserPointers();
	for (int i = 0; i < numLas;i++) {
		LaserPointer* laser = new LaserPointer();
		laser->spawn(m_LM.getLaserPos(),GRAVITY,m_GameTimeTotal,m_LM.getLaserDir(),m_ArrayLevel);
		m_LaserPointerList.push_back(laser);
	}
}

/**
*	Recreate the Window with new values
*/
void Engine::refreshWindow() {
	m_Window.create(sf::VideoMode(resolution.x, resolution.y),
		"Shadow Operative",
		m_windowedStatus);
	m_Window.setFramerateLimit(m_frameRate);
	m_Window.setVerticalSyncEnabled(m_vSyncActive);
}

/**
*	Calculated the Distance between two objects using their x,y(Sf::Vecor2f) coordinates
*/
float Engine::calcDistance(sf::Vector2f posOne, sf::Vector2f posTwo) {
	float distance;
	float distancex = ((posOne.x - posTwo.x) * (posOne.x - posTwo.x));
	float distancey = ((posOne.y - posTwo.y) * (posOne.y - posTwo.y));

	return distance = sqrt(distancex - distancey);
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