/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description	...
*/

#include "LevelManager.h"
#include "Engine.h"

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
}
int** LevelManager::nextLevel(sf::VertexArray& rVaLevel) {
	m_LevelSize.x = 0;
	m_LevelSize.y = 0;

	// Get the next level
	/*m_CurrentLevel++;
	if (m_CurrentLevel > NUM_LEVELS) {
		m_CurrentLevel = 1;
		m_TimeModifier -= .1f;
	}*/

	// Load the appropriate level from a text file
	std::string levelToLoad;

	switch (m_CurrentLevel)	{

	case 1:
		levelToLoad = "levels/level1.txt";
		m_StartPosition.x = 5;
		m_StartPosition.y = 5;
		m_BaseTimeLimit = 30.0f;
		break;

	case 2:
		levelToLoad = "levels/level2.txt";
		m_StartPosition.x = 100;
		m_StartPosition.y = 3600;
		m_BaseTimeLimit = 100.0f;
		break;
	case 3:
		levelToLoad = "levels/level3.txt";
		m_StartPosition.x = 1250;
		m_StartPosition.y = 0;
		m_BaseTimeLimit = 30.0f;
		break;
		/*
	case 4:
		levelToLoad = "levels/level4.txt";
		m_StartPosition.x = 50;
		m_StartPosition.y = 200;
		m_BaseTimeLimit = 50.0f;
		break;*/
	default:
		std::cout << "Map had a promblem" << std::endl;
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
	std::string row;
	sf::Vector2i temp;
	int verticalOffset;
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
				arrayLevel[y][x] = '0';
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
				arrayLevel[y][x] = '0';
				break;
			case 'd':
				//closed Door
				temp.x = x;
				temp.y = y;
				m_DoorPosition.push_back(temp);
				m_DoorType.push_back('d');
				arrayLevel[y][x] = '0';
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
				arrayLevel[y][x] = 'z';
				break;
			case 'n':
				arrayLevel[y][x] = 'n';
				break;
			case 'x':
				arrayLevel[y][x] = 'x';
				break;
			case 'v':
				arrayLevel[y][x] = 'v';
				break;
			case 'm':
				arrayLevel[y][x] = 'm';
				break;
			case 'f':
				arrayLevel[y][x] = 'f';
				break;
			case 'a':
				arrayLevel[y][x] = 'a';
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
				verticalOffset = 28;  // End game event.
				break;
			case 'o':
				verticalOffset = 29;  // End game event.
				break;
			case 'r':
				verticalOffset = 30;  // End game event.
				break;
			case 'l':
				verticalOffset = 31;  // End game event.
				break;
			}
			verticalOffset *= TILE_SIZE;
			//std::cout << arrayLevel[y][x] << std::endl;;

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

sf::Vector2i LevelManager::getLevelSize() {
	return m_LevelSize;
}

int LevelManager::getCurrentLevel() {
	return m_CurrentLevel;
}

float LevelManager::getTimeLimit() {
	return m_BaseTimeLimit * m_TimeModifier;
}
sf::Vector2i LevelManager::getStartPosition() {
	return m_StartPosition;
}

sf::Vector2i LevelManager::getEnemyPosition(){
	sf::Vector2i temp = m_EnemyPosition.back();
	m_EnemyPosition.pop_back();
	return temp;
}
int LevelManager::getNumOfEnemies(){
	return m_EnemyPosition.size();
}

int LevelManager::getNumOfItems() {
	return m_ItemType.size();
}
char LevelManager::getItemType(){
	char temp = m_ItemType.back();
	m_ItemType.pop_back();
	return temp;
}
sf::Vector2i LevelManager::getItemPos(){
	sf::Vector2i itemTemp = m_ItemPosition.back();
	m_ItemPosition.pop_back();
	return itemTemp;
}

int LevelManager::getNumOfDoors(){
	return m_DoorPosition.size();
}
sf::Vector2i LevelManager::getDoorPos() {
	sf::Vector2i doorTemp = m_DoorPosition.back();
	m_DoorPosition.pop_back();
	return doorTemp;
}
char LevelManager::getDoorType(){
	char door = m_DoorType.back();
	m_DoorType.pop_back();
	return door;
}
int LevelManager::getNumSwitches() {
	return m_SwitchPosition.size();
}
sf::Vector2i LevelManager::getSwitchPos() {
	sf::Vector2i switchTemp = m_SwitchPosition.back();
	m_SwitchPosition.pop_back();
	return switchTemp;
}