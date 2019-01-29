/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description	...
*/

#include "Enemy.h"

/**
* Spawns in the enemy Gives hime a sprite.
*/
void Enemy::spawn(sf::Vector2i startPosition, float gravity, sf::Time gameStart) {
	//std::cout << "\nEnemy spawn";
	this->m_SpawnPosition = startPosition;
	this->m_Position = (sf::Vector2f)m_SpawnPosition;
	m_Position.x = m_Position.x * TILE_SIZE;
	m_Position.y = m_Position.y * TILE_SIZE;
	m_Gravity = gravity;
	//The sprite for the enemy.
	m_Sprite = sf::Sprite(TextureHolder::GetTexture(
		"graphics/D-EnemyRight.png"));
	//Sets the sprite image to the location of the enemy. 
	m_Sprite.setPosition(this->m_Position);
	awarenessOfPlayer = 0.0f;
	lastDetectionEvent = gameStart;
	detectMeter.setSize(sf::Vector2f(10, this->getAwareness()));
	detectMeter.setFillColor(sf::Color::Red);
	detectMeter.setPosition(this->getCenter().x - 5, this->getCenter().y - 30);
	laserRange = detectionDistance;
	this->m_Direction = Direction::LEFT;
	cone.getCone().setPoint(0, m_Position);
}

/**
* This Update function will update the enemy every frame.
*This will mave the enemy and change the sprite of the enemy from left to right. 
*/
void Enemy::update(float elapsedTime, int** m_ArrayLevel/*, sf::Vector2f playPos*/) {
	if (concious) {
		// Make a rect for all his parts
		patrolValid = false;
		sf::FloatRect detectionZone = getPosition();

		//update detection meter
		detectMeter.setSize(sf::Vector2f(10, this->getAwareness()));
		detectMeter.setPosition(this->getCenter().x - 5, this->getCenter().y - 30);

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
				for (int y = startY; y < endY; y++) {
					// Initialize the starting position of the current block
					block.left = x * TILE_SIZE;
					block.top = y * TILE_SIZE;
					if (m_ArrayLevel[y][x] == 'T' || m_ArrayLevel[y - 1][x] == 'T') {
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
			m_Direction++;
			patrolValid = true;
		}


		switch (m_Direction) {
		case PlayableCharacter::Direction::LEFT:
			this->m_Position.x += this->m_Speed*elapsedTime;
			//Changes the enemy to look left.
			m_Sprite = sf::Sprite(TextureHolder::GetTexture(
				"graphics/D-EnemyLeft.png"));
			break;
		case PlayableCharacter::Direction::RIGHT:
			this->m_Position.x -= this->m_Speed*elapsedTime;
			//Changes the enemy to look Right.
			m_Sprite = sf::Sprite(TextureHolder::GetTexture(
				"graphics/D-EnemyRight.png"));
			break;
		}
		if (this->m_Direction == PlayableCharacter::Direction::LEFT) {
			direction = 'f';
		}
		else if (this->m_Direction == PlayableCharacter::Direction::RIGHT) {
			direction = 'm';
		}
		m_Sprite.setPosition(this->m_Position);
		detectionDistance = reCalculateMaxRange(direction, m_ArrayLevel, maxDistance);
		//for (std::list<Door*>::iterator doorIt = doors.begin();
		//	doorIt != doors.end();doorIt++) {
		//	if (this->getCone().getGlobalBounds().intersects((*doorIt)->getPosition())) {
		//		if (calcDistance(this->getCenter(), (*doorIt)->getCenter()) < detectionDistance) {
		//			detectionDistance = calcDistance(this->getCenter(), (*doorIt)->getCenter());
		//		}
		//	}
		//}

		if (m_Direction == PlayableCharacter::Direction::LEFT) {
			cone.updateConePos(this->m_Position, this->detectionDistance, this->sightAngle, true);
		}
		else {
			cone.updateConePos(this->m_Position, this->detectionDistance, this->sightAngle, false);
		}
	}
	else if (m_Action == Action::CROUCHING) {
		m_Sprite = sf::Sprite(TextureHolder::GetTexture(
			"graphics/Crate.png"));
		m_Sprite.setPosition(this->m_Position);
	}
	else { this->regen(elapsedTime); }
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
void Enemy::toggleTargeting(SoundManager& m_SM) {
	//	...
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
void Enemy::increaseAwarenessLevel(sf::Vector2f playPos, int detectionLevel,sf::Time gameTimeTotal,
	SoundManager& m_SM) {
	switch (detectionLevel)	{
	case 1: 
		//std::cout << "\nAwareness 1";
		if (calcDistance(playPos, this->getCenter()) <= 50) {
			std::cout << "\nDistance: <50";
			awarenessOfPlayer += 1.0;
		}
	case 2:
		//std::cout << "\nAwareness 2";
		if (calcDistance(playPos, this->getCenter()) > 50) {
			std::cout<<"\nDistance: 50+";
			awarenessOfPlayer += 1.5;
		}
		break;
	case 3:
		//std::cout << "\nAwareness 3";
		if (calcDistance(playPos, this->getCenter()) > 100) {
			std::cout << "\nDistance: 100+";
			awarenessOfPlayer += 2.0;
		}
		break;
	}
	//std::cout << "\nDetectionLevel" << detectionLevel;
	m_SM.playEnemyDetectionLevel(detectionLevel);
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
*	Apply damage(take from health) when called
*/
void Enemy::takeDamage(float shotPower) {
	if (this->isConscious())	{
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
*	Return whether or not The character is Concious
*/
bool Enemy::isConscious() {
	return concious;
}

/**
*	Increases the Characters Health relative to the amount of time passed 
		and their regenRate variable called once per frame
*/
void Enemy::regen(float elapsedTime) {
	//std::cout << "\nCALLING REGEN!!!";
	if (health < maxHealth)	{
		if (this->isConscious())	{
			//std::cout << "\nconscious";
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
			//std::cout << "\nNot conscious";
			if ((health + (regenRate / 2)) * elapsedTime <= maxHealth) {
				/*std::cout << "\nhealth:" << health << " + (regenRate / 2) " << (regenRate / 2)
					<< " * elapsedTime: " << elapsedTime << " = " << (health + ((regenRate / 2) * elapsedTime));*/
				health += ((regenRate / 2) * elapsedTime);
			}
			else {
				//std::cout << "\nHealth at max";
				health = maxHealth;
			}
		}
		//std::cout << "\nRegen complete Health is now" << this->health;
	}
	if ((health >= maxHealth) && (!concious))
	{
		std::cout << "\nConcious";
		concious = true;
	}
	
}

/**
*
*/
sf::String Enemy::getClassName() {
	return(sf::String("Enemy"));
}
/*
*	Find if Laser Hits a wall
*/
double Enemy::reCalculateMaxRange(char dir, int** m_ArrayLevel, double laserRange) {
	int x = (this->m_Position.x / TILE_SIZE);
	int y = (this->m_Position.y / TILE_SIZE);
	double calculatedrange = 0;
	if (this->getClassName() == "LaserPointer") {
		calculatedrange = 75;
		int y = (this->m_Position.y / TILE_SIZE);
	}
	else if (this->getClassName() == "Enemy") {
		int y = (this->getCone().getPoint(0).y / TILE_SIZE) - 1;
		y *= (0.5);
		calculatedrange = 20;
	}
	else if (this->getClassName() == "Camera") {
		if ((this->getCone().getPoint(0).y / TILE_SIZE) != 0) {
			y = (this->getCone().getPoint(0).y / TILE_SIZE)-1;
			x = (this->getCone().getPoint(0).x / TILE_SIZE);
		}
		calculatedrange = 30;
	}

	if (dir == 'a') {//UP
		for (int i = 1;i < (laserRange / TILE_SIZE);++i) {
			
			if ((m_ArrayLevel[y - i][x] == 0)|| (m_ArrayLevel[y - i][x] == 'T')
				|| (m_ArrayLevel[y - i][x] == 48) || (m_ArrayLevel[y - i][x] == 84)) {
				calculatedrange += TILE_SIZE;
			}
			else {
				break;
			}
		}
	}
	else if (dir == 'n') {//DOWN
		for (int i = 1;i < (laserRange / TILE_SIZE);++i) {
			if ((m_ArrayLevel[y + i][x] == 0) || (m_ArrayLevel[y + i][x] == 'T')
				|| (m_ArrayLevel[y + i][x] == 48) || (m_ArrayLevel[y + i][x] == 84)) {
				calculatedrange += TILE_SIZE;
			}
			else {
				break;
			}
		}
	}
	else if (dir == 'm') {//LEFT
		for (int i = 1;i < (laserRange / TILE_SIZE);++i) {
			if ((m_ArrayLevel[y][x - i] == 0) || (m_ArrayLevel[y][x - i] == 'T')
				|| (m_ArrayLevel[y][x - i] == 48) || (m_ArrayLevel[y][x - i] == 84)) {
				calculatedrange += TILE_SIZE;
			}
			else {
				break;
			}
		}
	}
	else if (dir == 'f') {//RIGHT
		for (int i = 1;i < (laserRange / TILE_SIZE);++i) {
			if ((m_ArrayLevel[y][x + i] == 0)|| (m_ArrayLevel[y][x + i] == 'T')
				|| (m_ArrayLevel[y][x+i] == 48) || (m_ArrayLevel[y][x+i] == 84)) {
				calculatedrange += TILE_SIZE;
			}
			else {
				break;
			}
		}
	}
	return calculatedrange;
}
/*
*	Virtual function never intended to be called
*/
bool Enemy::isTargeting() {
	return false;
}