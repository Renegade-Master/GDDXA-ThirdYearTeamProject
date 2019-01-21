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
	assert (m_ItemType.size() == 0);
	assert(m_ItemPosition.size() == 0);
	m_ItemPosition.clear();
}
int** LevelManager::nextLevel(sf::VertexArray& rVaLevel) {
	m_LevelSize.x = 0;
	m_LevelSize.y = 0;

	// Get the next level
	m_CurrentLevel++;
	if (m_CurrentLevel > NUM_LEVELS) {
		m_CurrentLevel = 1;
		m_TimeModifier -= .1f;
	}

	// Load the appropriate level from a text file
	std::string levelToLoad;
	switch (m_CurrentLevel)	{

	case 1:
		levelToLoad = "levels/level222.txt";
		m_StartPosition.x = 5;
		m_StartPosition.y = 5;
		m_BaseTimeLimit = 30.0f;
		break;

	/*case 2:
		levelToLoad = "levels/level222.txt";
		m_StartPosition.x = 100;
		m_StartPosition.y = 3600;
		m_BaseTimeLimit = 100.0f;
		break;*/

	/*case 3:
		levelToLoad = "levels/level3.txt";
		m_StartPosition.x = 1250;
		m_StartPosition.y = 0;
		m_BaseTimeLimit = 30.0f;
		break;

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
			case '3':
				temp.x = x;
				temp.y = y;
				m_ItemPosition.push_back(temp);
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
				arrayLevel[y][x] = 'D';
				break;
			case 'd':
				arrayLevel[y][x] = 'd';
				break;
			case 'b':
				arrayLevel[y][x] = 'b';
				break;
			case 's':
				arrayLevel[y][x] = 's';
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
			case 'B':
				temp.x = x;
				temp.y = y;
				m_ItemPosition.push_back(temp);
				m_ItemType.push_back('B');
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
			case 'r':
				verticalOffset = 0;  // We want a transparent tile here
				break;
			case 'z':
				verticalOffset = 20;  // We want a transparent tile here
				break;
			case 'n':
				verticalOffset = 24;  // We want a transparent tile here
				break;
			case 'x':
				verticalOffset = 21;  // We want a transparent tile here
				break;
			case 'v':
				verticalOffset = 23;  // We want a transparent tile here
				break;
			case 'm':
				verticalOffset = 25;  // We want a transparent tile here
				break;
			case 'f':
				verticalOffset = 27;  // We want a transparent tile here
				break;
			case 'a':
				verticalOffset = 26;  // We want a transparent tile here
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

sf::Vector2i LevelManager::getEnemyPosition()
{
	sf::Vector2i temp = m_EnemyPosition.back();
	std::cout << "\nThis Enemy position: x." << temp.x<<" y,"<<temp.y;
	m_EnemyPosition.pop_back();
	return temp;
}

int LevelManager::getNumOfEnemies()
{
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
	sf::Vector2i temp = m_ItemPosition.back();
	m_ItemPosition.pop_back();
	return temp;
}