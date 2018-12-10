#include "Enemy.h"
#include "TextureHolder.h"
void Enemy::spawn(sf::Vector2f startPosition, float gravity)
{
	m_SpawnPosition = startPosition;
	m_Position = m_SpawnPosition;
	m_Gravity = gravity;
	m_Sprite = sf::Sprite(TextureHolder::GetTexture(
		"graphics/thomas.png"));
	m_Sprite.setPosition(m_Position);
	m_RightPressed = true;
	m_LeftPressed = false;
}
void Enemy::update(char** m_ArrayLevel)
{
	//// Make a rect for all his parts
	//patrolValid = false;
	//sf::FloatRect detectionZone = getPosition();

	//const int TILE_SIZE = 50;
	//// Make a FloatRect to test each block
	//sf::FloatRect block;

	//block.width = TILE_SIZE;
	//block.height = TILE_SIZE;

	////Check Zone around characters
	//int startX = (int)(detectionZone.left / TILE_SIZE) - 1;
	//int startY = (int)(detectionZone.top / TILE_SIZE) - 1;
	//int endX = (int)(detectionZone.left / TILE_SIZE) + 2;
	//int endY = (int)(detectionZone.top / TILE_SIZE) + 3;
	////see if the enemy is moving and if not Choose a direction to patrol
	//for (int x = startX; x < endX; x++)
	//{
	//	for (int y = startY; y < endY; y++)
	//	{
	//		// Initialize the starting position of the current block
	//		block.left = x * TILE_SIZE;
	//		block.top = y * TILE_SIZE;
	//		if (m_ArrayLevel[y][x] == 'T')
	//		{
	//			if (getFeet().intersects(block))
	//			{
	//				patrolValid = true;
	//			}
	//		}
	//	}
	//}
	//if (!patrolValid)
	//{
	//	//alter patrol route
	//}
}
