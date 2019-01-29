/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description	...
*/

#include "LevelManager.h"
#include "Engine.h"

/**
*	Default Constructor
*/
LevelManager::LevelManager(){
	//These keep the game from crashing if the levels have no Items,Doors or Switches
	assert (m_ItemType.size() == 0);
	assert(m_ItemPosition.size() == 0);
	m_ItemPosition.clear();
	assert(m_DoorPosition.size() == 0);
	assert(m_DoorType.size() == 0);
	m_DoorPosition.clear();
	assert(m_SwitchPosition.size() == 0);
	m_SwitchPosition.clear();
	assert(m_CameraPosition.size() == 0);
	assert(m_CameraType.size() == 0);
	m_CameraPosition.clear();
}

/**
*	Load Next Level of the game
*/
int** LevelManager::nextLevel(sf::VertexArray& rVaLevel) {
	m_LevelSize.x = 0;
	m_LevelSize.y = 0;

	// Load the appropriate level from a text file
	std::string levelToLoad;

	switch (m_CurrentLevel)	{
	case 1:
		//This is level 1.
		levelToLoad = "levels/level1.txt";
		m_StartPosition.x = 5;
		m_StartPosition.y = 5;
		break;

	case 2:
		//This is level 2. 
		levelToLoad = "levels/level2.txt";
		m_StartPosition.x = 100;
		m_StartPosition.y = 3600;
		break;

	case 3:
		//This is level 3
		levelToLoad = "levels/level3.txt";
		m_StartPosition.x = 1250;
		m_StartPosition.y = 0;
		break;

	default:
		std::cout << "Map had a problem" << std::endl;
		break;
	}

	std::ifstream inputFile(levelToLoad);
	std::string s;

	// Count the number of rows in the file
	while (getline(inputFile, s)) {
		++m_LevelSize.y;
	}

	// Store the length of the rows
	m_LevelSize.x = s.length();

	// Go back to the start of the file
	inputFile.clear();
	inputFile.seekg(0, std::ios::beg);

	// Prepare the 2d array to hold the int values from the file
	int** arrayLevel = new int*[m_LevelSize.y];
	for (int i = 0; i < m_LevelSize.y; ++i)	{
		// Add a new array into each array element
		arrayLevel[i] = new int[m_LevelSize.x];
	}

	// Loop through the file and store all the values in the 2d array
	std::string row = NULL;
	sf::Vector2i temp;
	int verticalOffset = 0;
	int y = 0;

	while (inputFile >> row) {
		for (int x = 0; x < row.length(); x++) {
			const char val = row[x];
			arrayLevel[y][x] = atoi(&val);	//Warning here is actually leveraged by the game code

			switch (row[x]) {
			case 'E':
				temp.x = x;
				temp.y = y;
				m_EnemyPosition.push_back(temp);
				arrayLevel[y][x] = 'T';
				break;
			case 'T':
				arrayLevel[y][x] = 'T';
				break;
			case '9':
				//static Door
				temp.x = x;
				temp.y = y;
				m_DoorPosition.push_back(temp);
				m_DoorType.push_back('9');
				arrayLevel[y][x] = '9';
				break;
			case 'P':
				m_StartPosition.x = x * TILE_SIZE;
				m_StartPosition.y = y * TILE_SIZE;
				break;
			case '4':
				m_EndPosition.x = x;
				m_EndPosition.y = y;
				break;
			case 'D':
				//open Door
				temp.x = x;
				temp.y = y;
				m_DoorPosition.push_back(temp);
				m_DoorType.push_back('D');
				arrayLevel[y][x] = 'D';
				break;
			case 'd':
				//closed Door
				temp.x = x;
				temp.y = y;
				m_DoorPosition.push_back(temp);
				m_DoorType.push_back('d');
				arrayLevel[y][x] = 'd';
				break;
			case 'b':
				arrayLevel[y][x] = 'b';
				break;
			case 's':
				//switch
				temp.x = x;
				temp.y = y;
				m_SwitchPosition.push_back(temp);
				arrayLevel[y][x] = '0';
				break;
			case 'k':
				arrayLevel[y][x] = 'k';
				break;
			case 'j':
				arrayLevel[y][x] = 'j';
				break;
			case 'F':
				arrayLevel[y][x] = 'F';
				break;
			case 'G':
				arrayLevel[y][x] = 'G';
				break;
			case 'H':
				arrayLevel[y][x] = 'H';
				break;
			case 'u':
				arrayLevel[y][x] = 'u';
				break;
			case 'r':
				arrayLevel[y][x] = 'r';
				break;
			case 'z':
				temp.x = x;
				temp.y = y;
				m_CameraPosition.push_back(temp);
				m_CameraType.push_back('z');
				arrayLevel[y][x] = '0';
				break;
			case 'n':
				temp.x = x;
				temp.y = y;
				m_LaserPointerPos.push_back(temp);
				m_LaserDir.push_back('n');
				arrayLevel[y][x] = '0';
				break;
			case 'x':
				temp.x = x;
				temp.y = y;
				m_CameraPosition.push_back(temp);
				m_CameraType.push_back('x');
				arrayLevel[y][x] = '0';
				break;
			case 'c':
				temp.x = x;
				temp.y = y;
				m_CameraPosition.push_back(temp);
				m_CameraType.push_back('c');
				arrayLevel[y][x] = '0';
				break;
			case 'v':
				temp.x = x;
				temp.y = y;
				m_CameraPosition.push_back(temp);
				m_CameraType.push_back('v');
				arrayLevel[y][x] = '0';
				break;
			case 'm':
				temp.x = x;
				temp.y = y;
				m_LaserPointerPos.push_back(temp);
				m_LaserDir.push_back('m');
				arrayLevel[y][x] = '0';
				break;
			case 'f':
				temp.x = x;
				temp.y = y;
				m_LaserPointerPos.push_back(temp);
				m_LaserDir.push_back('f');
				arrayLevel[y][x] = '0';
				break;
			case 'a':
				temp.x = x;
				temp.y = y;
				m_LaserPointerPos.push_back(temp);
				m_LaserDir.push_back('a');
				arrayLevel[y][x] = '0';
				break;
			case 'Q':
				arrayLevel[y][x] = 'Q';
				break;
			case 'B':
				temp.x = x;
				temp.y = y;
				m_ItemPosition.push_back(temp);
				m_ItemType.push_back('B');
				arrayLevel[y][x] = 0;
				break;
			case 'i':
				arrayLevel[y][x] = 'i';
				break;
			case 'o':
				arrayLevel[y][x] = 'o';
				break;
			case 'l':
				arrayLevel[y][x] = 'l';
				break;
			case 'q':
				arrayLevel[y][x] = 'q';
				break;
			}
		}
		y++;
	}

	// close the file
	inputFile.close();

	// What type of primitive are we using?
	rVaLevel.setPrimitiveType(sf::Quads);

	// Set the size of the vertex array
	rVaLevel.resize(m_LevelSize.x * m_LevelSize.y * VERTS_IN_QUAD);

	// Start at the beginning of the vertex array
	int currentVertex = 0;

	for (int x = 0; x < m_LevelSize.x; x++)	{
		for (int y = 0; y < m_LevelSize.y; y++)	{
			// Position each vertex in the current quad
			rVaLevel[currentVertex + 0].position =
				sf::Vector2f(x * TILE_SIZE, y * TILE_SIZE);

			rVaLevel[currentVertex + 1].position =
				sf::Vector2f((x * TILE_SIZE) + TILE_SIZE, y * TILE_SIZE);

			rVaLevel[currentVertex + 2].position =
				sf::Vector2f((x * TILE_SIZE) + TILE_SIZE, (y * TILE_SIZE) + TILE_SIZE);

			rVaLevel[currentVertex + 3].position =
				sf::Vector2f((x * TILE_SIZE), (y * TILE_SIZE) + TILE_SIZE);
			
			// Which tile from the sprite sheet should we use
			verticalOffset = arrayLevel[y][x];
			switch(arrayLevel[y][x]) {
			case 'D':
				verticalOffset = 10;//Open Door
				break;
			case 'd':
				verticalOffset = 19;//Yellow Door
				break;
			case 'b':
				verticalOffset = 11;//Cable
				break;
			case 's':
				verticalOffset = 12;//Switch
				break;
			case 'k':
				verticalOffset = 13;//Red Barrel
				break;
			case 'j':
				verticalOffset = 14;//Green Barrel
				break;
			case 'u':
				verticalOffset = 15;//Crate
				break;
			case 'F':
				verticalOffset = 16;//Left Fence
				break;
			case 'G':
				verticalOffset = 17;//Middle Fence
				break;
			case 'H':
				verticalOffset = 18;//Right Fence
				break;
			case 'E':
				verticalOffset = 0;  // We want a transparent tile here				
				break;
			case 'P':
				verticalOffset = 0;  // We want a transparent tile here
				break;
			case 'T':
				verticalOffset = 0;  // We want a transparent tile here
				break;
			case 'z':
				verticalOffset = 20;  //This is a camera looking down.
				break;
			case 'n':
				verticalOffset = 24;  // This is a lazer looking down.
				break;
			case 'x':
				verticalOffset = 21;  // This is a camera looking left
				break;
			case 'v':
				verticalOffset = 23;  // This is a camera looking right.
				break;
			case 'm':
				verticalOffset = 25;  // This is a lazer looking left.
				break;
			case 'f':
				verticalOffset = 27;  // This is a lazer looking right.
				break;
			case 'a':
				verticalOffset = 26;  // This is a lazer looking up.
				break;
			case 'Q':
				verticalOffset = 0;  // End game event.
				break;
			case 'i':
				verticalOffset = 28;  // This is a frame that is the crane.
				break;
			case 'o':
				verticalOffset = 29;  // This is the end of the crane.
				break;
			case 'r':
				verticalOffset = 30;  // This is the weight of the crane.
				break;
			case 'l':
				verticalOffset = 31;  // This is a line on the crane.
				break;
			case 'q':
				verticalOffset = 0;  // Play the video for the end game credits.
				break;
			}

			verticalOffset *= TILE_SIZE;

			rVaLevel[currentVertex + 0].texCoords =
				sf::Vector2f(0, 0 + verticalOffset);

			rVaLevel[currentVertex + 1].texCoords =
				sf::Vector2f(TILE_SIZE, 0 + verticalOffset);

			rVaLevel[currentVertex + 2].texCoords =
				sf::Vector2f(TILE_SIZE, TILE_SIZE + verticalOffset);

			rVaLevel[currentVertex + 3].texCoords =
				sf::Vector2f(0, TILE_SIZE + verticalOffset);

			// Position ready for the next four vertices
			currentVertex = currentVertex + VERTS_IN_QUAD;
		}
	}
	return arrayLevel;
}

/**
*	Get X*Y size of current Level
*/
sf::Vector2i LevelManager::getLevelSize() {
	return m_LevelSize;
}

/**
*	Get Current Level e.g Level 1,Level 2...
*/
int LevelManager::getCurrentLevel() {
	return m_CurrentLevel;
}

/**
*	Get Starting Position of Player character for this level
*/
sf::Vector2i LevelManager::getStartPosition() {
	return m_StartPosition;
}

/**
*	Get the spawn coordinates of Enemies by popping them off the back of the queue
*/
sf::Vector2i LevelManager::getEnemyPosition(){
	sf::Vector2i temp = m_EnemyPosition.back();
	m_EnemyPosition.pop_back();
	return temp;
}

/**
*	Get size of List of Enemy coordinates
*/
int LevelManager::getNumOfEnemies(){
	return m_EnemyPosition.size();
}

/**
*	Get size of List of Items coordinates
*/
int LevelManager::getNumOfItems() {
	return m_ItemType.size();
}
/**
*	Get Item type by popping the identifier off the back of the queue
*/
char LevelManager::getItemType(){
	char temp = m_ItemType.back();
	m_ItemType.pop_back();
	return temp;
}
/**
*	Get the spawn coordinates of Items by popping them off the back of the queue
*/
sf::Vector2i LevelManager::getItemPos(){
	sf::Vector2i itemTemp = m_ItemPosition.back();
	m_ItemPosition.pop_back();
	return itemTemp;
}
/**
*	Get size of List of Doors coordinates
*/
int LevelManager::getNumOfDoors(){
	return m_DoorPosition.size();
}
/**
*	Get the spawn coordinates of Doors by popping them off the back of the queue
*/
sf::Vector2i LevelManager::getDoorPos() {
	sf::Vector2i doorTemp = m_DoorPosition.back();
	m_DoorPosition.pop_back();
	return doorTemp;
}
/**
*	Get Door type by popping the identifier off the back of the queue
*/
char LevelManager::getDoorType(){
	char door = m_DoorType.back();
	m_DoorType.pop_back();
	return door;
}

/**
*	Get size of List of Switches coordinates
*/
int LevelManager::getNumSwitches() {
	return m_SwitchPosition.size();
}

/**
*	Get the spawn coordinates of Switches by popping them off the back of the queue
*/
sf::Vector2i LevelManager::getSwitchPos() {
	sf::Vector2i switchTemp = m_SwitchPosition.back();
	m_SwitchPosition.pop_back();
	return switchTemp;
}

/**
*	Get size of List of Cameras coordinates
*/
int LevelManager::getNumCams() {
	return m_CameraPosition.size();
}

/**
*	Get the spawn coordinates of Camera's by popping them off the back of the queue
*/
sf::Vector2i LevelManager::getCamPos() {
	sf::Vector2i camTemp = m_CameraPosition.back();
	m_CameraPosition.pop_back();
	return camTemp;
}

/**
*	Get Camera type by popping the identifier off the back of the queue
*/
char LevelManager::getCamDir() {
	char cam = m_CameraType.back();
	m_CameraType.pop_back();
	return cam;
}

/**
*	Get size of List of Laserpointer's coordinates
*/
int LevelManager::getNumLaserPointers() {
	return m_LaserPointerPos.size();
}

/**
*	Get the spawn coordinates of LaserPointer by popping them off the back of the queue
*/
sf::Vector2i LevelManager::getLaserPos() {
	sf::Vector2i lasTemp = m_LaserPointerPos.back();
	m_LaserPointerPos.pop_back();
	return lasTemp;
}

/**
*	Get Laserpointer direction by popping the identifier off the back of the queue
*/
char LevelManager::getLaserDir() {
	char lasType = m_LaserDir.back();
	m_LaserDir.pop_back();
	return lasType;
}