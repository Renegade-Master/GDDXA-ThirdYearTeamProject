/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description
*/

#include "Enemy.h"
#include "TextureHolder.h"
#include <iostream>

void Enemy::spawn(sf::Vector2i startPosition, float gravity) {
	//std::cout << "\nEnemy spawn";
	this->m_SpawnPosition = startPosition;
	this->m_Position = (sf::Vector2f)m_SpawnPosition;
	m_Position.x = m_Position.x * 50;
	m_Position.y = m_Position.y * 50;
	//m_Position.x = m_SpawnPosition.x;
	//m_Position.y = m_SpawnPosition.y;
	m_Gravity = gravity;
	m_Sprite = sf::Sprite(TextureHolder::GetTexture(
		"graphics/Sprites/R_idle_1.png"));
	m_Sprite.setPosition(this->m_Position);
	m_RightPressed = true;
	m_LeftPressed = false;
}

void Enemy::update(float elapsedTime, int** m_ArrayLevel) {
	// Make a rect for all his parts
	patrolValid = false;
	sf::FloatRect detectionZone = getPosition();

	const int TILE_SIZE = 50;
	// Make a FloatRect to test each block
	sf::FloatRect block;

	block.width = TILE_SIZE;
	block.height = TILE_SIZE;

	//Check Zone around characters
	int startX = (int)(detectionZone.left / TILE_SIZE) - 1;
	int startY = (int)(detectionZone.top / TILE_SIZE) - 1;
	int endX = (int)(detectionZone.left / TILE_SIZE) + 2;
	int endY = (int)(detectionZone.top / TILE_SIZE) + 3;
	//see if the enemy is moving and if not Choose a direction to patrol
	if (sincePatrolAlter <= 0)
	{
		for (int x = startX; x < endX; x++)
		{
			for (int y = startY; y < endY; y++)
			{
				// Initialize the starting position of the current block
				block.left = x * TILE_SIZE;
				block.top = y * TILE_SIZE;
				if (m_ArrayLevel[y][x] == 'T' || m_ArrayLevel[y - 1][x] == 'T')
				{
					//std::cout << "\nChecking patrol loop";
					if (getFeet().intersects(block))
					{
						//std::cout << "\\nNot intersect block";
						patrolValid = false;
						sincePatrolAlter = 8;
					}
					else
					{
						//std::cout << "\nIntersecting block";
						patrolValid = true;
					}
				}
			}
		}
	}
	else
	{
		sincePatrolAlter--;
	}
	if (!patrolValid)
	{
		move++;
		patrolValid = true;
	}
	
	
	switch (move)
	{
	case patrolLeft:
		this->m_Position.x += this->m_Speed*elapsedTime;
		break;
	case patrolRight:
		this->m_Position.x -= this->m_Speed*elapsedTime;
		break;
	}
	m_Sprite.setPosition(this->m_Position);
	if (move == patrolLeft)
	{
		cone.updateConePos(this->m_Position, this->detectionDistance, this->sightAngle, true);
	}
	else
	{
		cone.updateConePos(this->m_Position, this->detectionDistance, this->sightAngle, false);
	}
}
Enemy::patrolDir& operator++(Enemy::patrolDir& mv, int)
{
	switch (mv)
	{
	case Enemy::patrolLeft:
		mv = Enemy::patrolRight;
		return(mv);
	case Enemy::patrolRight:
		mv = Enemy::patrolLeft;
		return(mv);
	}
}
bool Enemy::handleInput()
{
	return true;
}
void Enemy::alterPatrol(bool patrol)
{
	if (patrol)
	{
		patrolValid = true;
	}
	else
	{
		patrolValid = false;
	}
}
sf::FloatRect Enemy::getPosition() {
	return m_Sprite.getGlobalBounds();
}
bool Enemy::detectPlayer(sf::Vector2f playPos)
{
	return false;
}
sf::ConvexShape Enemy::getCone()
{
	return cone.getCone();
}
