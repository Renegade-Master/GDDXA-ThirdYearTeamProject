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
	m_Gravity = gravity;
	m_Sprite = sf::Sprite(TextureHolder::GetTexture(
		"graphics/Bob.png"));
	m_Sprite.setPosition(this->m_Position);
	awarenessOfPlayer = 0.0f;
	lastDetectionEvent = gameStart;
	detectMeter.setSize(sf::Vector2f(10, this->getAwareness()));
	detectMeter.setFillColor(sf::Color::Red);
	detectMeter.setPosition(this->getCenter().x - 5, this->getCenter().y - 30);
	laserRange = detectionDistance;
	this->m_Direction = Direction::LEFT;
}

/**aaaaa
*
*/
void Enemy::update(float elapsedTime, int** m_ArrayLevel/*, sf::Vector2f playPos*/) {
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
			break;
		case PlayableCharacter::Direction::RIGHT:
			this->m_Position.x -= this->m_Speed*elapsedTime;
			break;
		}
		if (this->m_Direction == PlayableCharacter::Direction::LEFT) {
			direction = 'm';
		}
		else if (this->m_Direction == PlayableCharacter::Direction::RIGHT) {
			direction = 'f';
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
	this->regen(elapsedTime);
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

//Changes the enmey into a crate.
void Enemy::EnemyCrate()
{
	m_SpriteCrate = sf::Sprite(TextureHolder::GetTexture(
		"graphics/Crate.png"));
	m_SpriteCrate.setPosition(this->m_Position);
	std::cout << "\nCROUCHING";
}

/**
*
*/
void Enemy::toggleTargeting() {
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
*	Find if Laser goes through wall
*/
double Enemy::reCalculateMaxRange(char dir, int** m_ArrayLevel, double laserRange) {
	int x = (this->m_Position.x / 50);
	int y = (this->m_Position.y / 50);
	//std::cout << "\n\n\n\ny= " << y;
	double calculatedrange = 0;
	if (this->getClassName() == "LaserPointer") {
		//std::cout << "\nLaserpointer";
		calculatedrange = 75;
		int y = (this->m_Position.y / 50);
	}
	else if (this->getClassName() == "Enemy") {
		//std::cout << "\nEnemy";
		int y = (this->getCone().getPoint(0).y / 50)-1;
		y *= (0.5);
		//y -= 1;
		 calculatedrange = 0;
	}
	//std::cout << "\n\nThis->m_Position " << this->m_Position.x << ", " << this->m_Position.y;
	//std::cout << "  Y= " << y<<" ,X"<<x;
	/*std::cout << "\ny= " << y;
	std::cout << "\nThis->getPosition() " << this->m_Position.x << " ," << this->m_Position.y;
	
	std::cout << "\ny= " << y;
	std::cout << "\nThis->getPosition() " << this->m_Position.x << " ," << this->m_Position.y;*/
	
	//Enemies only Move Left and Right
	//if (this->getClassName() == "Enemy") {
	//	//y -= 1;
	//	if (dir == 'm') {//LEFT
	//		for (int i = 0;i < (laserRange / 50);++i) {
	//			
	//			if ((m_ArrayLevel[y][x-i] == 0) || (m_ArrayLevel[y][x-i] == 'T')) {
	//				calculatedrange += 50;
	//			}
	//			else {
	//				break;
	//			}
	//		}
	//	}
	//	else if (dir == 'f') {//RIGHT
	//		for (int i = 0;i < (laserRange / 50);++i) {
	//			if ((m_ArrayLevel[y][x+i] == 0) || (m_ArrayLevel[y][x+i] == 'T')) {
	//				calculatedrange += 50;
	//			}
	//			else {
	//				break;
	//			}
	//		}
	//	}
	//	return calculatedrange;
	//}
	//LaserPointer implementation
	std::cout << "\nDirection" << dir;
		if (dir == 'a') {//UP
			for (int i = 1;i < (laserRange / 50);++i) {
				if ((m_ArrayLevel[y - i][x] == 0)|| (m_ArrayLevel[y - i][x] == 'T')
					|| (m_ArrayLevel[y - i][x] == 48) || (m_ArrayLevel[y - i][x] == 84)) {
					calculatedrange += 50;
				}
				else {
					break;
				}
			}
		}
		else if (dir == 'n') {//DOWN
			for (int i = 1;i < (laserRange / 50);++i) {
				if ((m_ArrayLevel[y + i][x] == 0) || (m_ArrayLevel[y + i][x] == 'T')
					|| (m_ArrayLevel[y + i][x] == 48) || (m_ArrayLevel[y + i][x] == 84)) {
					calculatedrange += 50;
				}
				else {
					break;
				}
			}
		}
		else if (dir == 'm') {//LEFT
			//std::cout << "\nLeft";
			for (int i = 1;i < (laserRange / 50);++i) {
				int block = int(m_ArrayLevel[y][x - i]);
				//std::cout << "\nBlock = " << block;

				if (this->getClassName() == sf::String("Enemy")) { 
					//std::cout<< "BREAK HERE" << std::endl;
				}

				if (	(block == 0)	|| (block == 'T')
					||	(block == 48)	|| (block == 84)) {

					//std::cout << "\nAll clear";
					calculatedrange += 50;
				}
				else {
					//std::cout << "\nHit Wall";
					break;
				}
			}
		}
		else if (dir == 'f') {//RIGHT
			for (int i = 1;i < (laserRange / 50);++i) {
				char block = m_ArrayLevel[y][x - i];
				//std::cout << "\nBlock = " << m_ArrayLevel[y][x - i];
				if ((m_ArrayLevel[y][x + i] == 0)|| (m_ArrayLevel[y][x + i] == 'T')
					|| (m_ArrayLevel[y][x+i] == 48) || (m_ArrayLevel[y][x+i] == 84)) {
					//std::cout << "\nAll clear";
					calculatedrange += 50;
				}
				else {
					//std::cout << "\nHit Wall";
					break;
				}
			}
		}
		//std::cout << "\nReturning: " << calculatedrange;
		return calculatedrange;
}