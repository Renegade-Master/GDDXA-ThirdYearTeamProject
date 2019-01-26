/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description	...
*/

#include "Enemy.h"

/**
*
*/
void Enemy::spawn(sf::Vector2i startPosition, float gravity, sf::Time gameStart) {
	//std::cout << "\nEnemy spawn";
	this->m_SpawnPosition = startPosition;
	this->m_Position = (sf::Vector2f)m_SpawnPosition;
	m_Position.x = m_Position.x * 50;
	m_Position.y = m_Position.y * 50;
	//m_Position.x = m_SpawnPosition.x;
	//m_Position.y = m_SpawnPosition.y;
	m_Gravity = gravity;
	/*m_Sprite = sf::Sprite(TextureHolder::GetTexture(
		"graphics/enemy2.png"));*/
	m_Sprite = sf::Sprite(TextureHolder::GetTexture(
		"graphics/bob.png"));
	m_Sprite.setPosition(this->m_Position);
	//m_RightPressed = true;
	//m_LeftPressed = false;
	awarenessOfPlayer = 0.0;
	lastDetectionEvent = gameStart;
	detectMeter.setSize(sf::Vector2f(10, this->getAwareness()));
	detectMeter.setFillColor(sf::Color::Red);
	detectMeter.setPosition(this->getCenter().x-5, this->getCenter().y - 30);
}

/**
*
*/
void Enemy::update(float elapsedTime, int** m_ArrayLevel) {
	if (concious) {
		// Make a rect for all his parts
		patrolValid = false;
		sf::FloatRect detectionZone = getPosition();

		//update detection meter
		detectMeter.setSize(sf::Vector2f(10, this->getAwareness()));
		detectMeter.setPosition(this->getCenter().x - 5, this->getCenter().y - 30);

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
		if (sincePatrolAlter <= 0) {
			for (int x = startX; x < endX; x++) {
				for (int y = startY; y < endY; y++)	{
					// Initialize the starting position of the current block
					block.left = x * TILE_SIZE;
					block.top = y * TILE_SIZE;
					if (m_ArrayLevel[y][x] == 'T' || m_ArrayLevel[y - 1][x] == 'T') {	{
						//std::cout << "\nChecking patrol loop";
						if (getFeet().intersects(block)) {
							//std::cout << "\\nNot intersect block";
							patrolValid = false;
							sincePatrolAlter = 8;
						}
						else {
							//std::cout << "\nIntersecting block";
							patrolValid = true;
						}
					}
				}
			}
		}
		else {
			sincePatrolAlter--;
		}
		if (!patrolValid) {
			move++;
			patrolValid = true;
		}


		switch (move) {
		case patrolLeft:
			this->m_Position.x += this->m_Speed*elapsedTime;
			break;
		case patrolRight:
			this->m_Position.x -= this->m_Speed*elapsedTime;
			break;
		}

		m_Sprite.setPosition(this->m_Position);
		
		if (move == patrolLeft) {
			cone.updateConePos(this->m_Position, this->detectionDistance, this->sightAngle, true);
		}
		else {
			cone.updateConePos(this->m_Position, this->detectionDistance, this->sightAngle, false);
		}
	}
	//(*it)->Enemy Regen
	//std::cout << "\nCalling REGEN!!!!!";
	this->regen(elapsedTime);
}

/**
*
*/
Enemy::patrolDir& operator++(Enemy::patrolDir& mv, int) {
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

/**
*
*/
void Enemy::handleInput() {
	// Doesn't seem to be anything to do here.
}

/**
*
*/
void Enemy::alterPatrol(bool patrol) {
	if (patrol)
	{
		patrolValid = true;
	}
	else
	{
		patrolValid = false;
	}
}

/**
*
*/
sf::FloatRect Enemy::getPosition() {
	return m_Sprite.getGlobalBounds();
}

/**
*
*/
bool Enemy::detectPlayer(sf::Vector2f playPos) {
	return false;
}

/**
*
*/
sf::ConvexShape Enemy::getCone() {
	return cone.getCone();
}

/**
*
*/
void Enemy::increaseAwarenessLevel(sf::Vector2f playPos, int detectionLevel,sf::Time gameTimeTotal) {
	switch (detectionLevel)	{
	case 1: 
		std::cout << "\nAwareness 1";
		if (calcDistance(playPos, this->getCenter()) <= 50) {
			std::cout << "\nDistance: <50";
			awarenessOfPlayer += 1.0;
		}
	case 2:
		std::cout << "\nAwareness 2";
		if (calcDistance(playPos, this->getCenter()) > 50) {
			std::cout<<"\nDistance: 50+";
			awarenessOfPlayer += 1.5;
		}
		break;
	case 3:
		std::cout << "\nAwareness 3";
		if (calcDistance(playPos, this->getCenter()) > 100) {
			std::cout << "\nDistance: 100+";
			awarenessOfPlayer += 2.0;
		}
		break;
	}
	lastDetectionEvent = gameTimeTotal;
}

/**
*
*/
float Enemy::getAwareness() {
	return awarenessOfPlayer;
}

/**
*
*/
float Enemy::getlastdetectTime() {
	return lastDetectionEvent.asMilliseconds();
}

/**
*
*/
double Enemy::calcDistance(sf::Vector2f playPos, sf::Vector2f thisPos) {
	double distance;
	double distancex = ((playPos.x - thisPos.x) * (playPos.x - thisPos.x));
	double distancey = ((playPos.y - thisPos.y) * (playPos.y - thisPos.y));

	return distance = sqrt(distancex - distancey);
}

/**
*
*/
sf::RectangleShape Enemy::getDetectMeter() {
	return detectMeter;
}

/**
*
*/
void Enemy::reduceAwareness(sf::Time gameTimeTotal) {
	awarenessOfPlayer--;
	lastDetectionEvent = gameTimeTotal;
}

/**
*
*/
void Enemy::takeDamage(float shotPower) {
	if (this->isConcious())	{
		health = health - shotPower * 3;
	}
	else {
		health = 0;
	}
	if (health <= 0) {
		concious = false;
	}
}

/**
*
*/
bool Enemy::isConcious() {
	return concious;
}

/**
*
*/
void Enemy::regen(float elapsedTime) {
	//std::cout << "\nCALLING REGEN!!!";
	if (health < maxHealth)	{
		if (this->isConcious())	{
			//std::cout << "\nConcious";
			if ((health + (regenRate * elapsedTime)) <= maxHealth) {
				/*std::cout << "\nhealth:" << health << " + regenRate " << regenRate
					<< " * elapsedTime: " << elapsedTime << " = " << health + (regenRate * elapsedTime);*/
				health += regenRate * elapsedTime;
			}
			else {
				//std::cout << "\nHealth at max";
				health = maxHealth;
			}
		}
		else {
			//std::cout << "\nNot Concious";
			if ((health + (regenRate / 2)) * elapsedTime <= maxHealth) {
				/*std::cout << "\nhealth:" << health << " + (regenRate / 2) " << (regenRate / 2)
					<< " * elapsedTime: " << elapsedTime << " = " << (health + ((regenRate / 2) * elapsedTime));*/
				health += (regenRate / 2) * elapsedTime;
			}
			else {
				//std::cout << "\nHealth at max";
				health = maxHealth;
			}
		}
		//std::cout << "\nRegen complete Health is now" << this->health;
	}
	if ((health == maxHealth) && (!concious)) {
		concious = true;
	}	
}