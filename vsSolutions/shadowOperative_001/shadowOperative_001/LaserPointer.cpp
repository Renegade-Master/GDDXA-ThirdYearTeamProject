/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description
*/
#include "LaserPointer.h"

/*
*	Default constructor for LaserPointer
*/
LaserPointer::LaserPointer() {
	m_Sprite = sf::Sprite(TextureHolder::GetTexture(
		"graphics/LaserPointer.png"));
}
/*
*	initialises the variables of the LaserPointer object
*/
void LaserPointer::spawn(sf::Vector2i startPosition, float gravity, sf::Time gameStart, char dir,int** m_ArrayLevel) {
	this->m_Position = sf::Vector2f(startPosition);
	this->m_Position.x = this->m_Position.x * TILE_SIZE;
	this->m_Position.y = this->m_Position.y * TILE_SIZE;

	this->m_Sprite.setOrigin(this->getCenter().x - this->getCenter().x + TILE_SIZE,
		this->getCenter().y - this->getCenter().y + 1);
	
	//Start ToggleEvent Timer
	lastToggleEvent = gameStart;
	active = true;
	maxLaserRange = laserRange;
	laserRange = reCalculateMaxRange(dir,m_ArrayLevel,laserRange);
	
	/*Orient the Object to the appropriate position
		and calculate the bounds of the connected laser object*/
	if (dir == 'a') {//UP
		this->m_Position.y += 75;
		m_Sprite.setPosition(this->m_Position);
		m_Sprite.setRotation(90.0f);
		this->laserOrig.x = this->m_Position.x - 30;
		this->laserOrig.y = this->m_Position.y - 70;
		this->laserDest.x = this->m_Position.x - 4;
		this->laserDest.y = this->m_Position.y - laserRange;
		this->visionLaser.updateLine(this->laserOrig, this->laserDest);
	}
	else if (dir == 'n') {//DOWN
		this->m_Position.y -= 25;
		m_Sprite.setPosition(this->m_Position);
		m_Sprite.setRotation(-90.0f);
		this->laserOrig.x = this->m_Position.x - 20;
		this->laserOrig.y = this->m_Position.y + 20;
		this->laserDest.x = this->m_Position.x + 4;
		this->laserDest.y = this->m_Position.y + laserRange;
		this->visionLaser.updateLine(this->laserOrig, this->laserDest);
	}
	else if (dir == 'm') {//LEFT
		this->m_Position.x += 75;
		m_Sprite.setPosition(this->m_Position);
		m_Sprite.setPosition(this->m_Position);
		this->laserOrig.x = this->m_Position.x - 70;
		this->laserOrig.y = this->m_Position.y - 20;
		this->laserDest.x = this->m_Position.x - laserRange;
		this->laserDest.y = this->m_Position.y;
		this->visionLaser.updateLine(this->laserOrig, this->laserDest);
	}
	else if (dir == 'f') {//RIGHT
		this->m_Position.x -= 25;
		this->m_Position.y += 25;
		m_Sprite.setPosition(this->m_Position);
		m_Sprite.setRotation(180.0f);
		this->laserOrig.x = this->m_Position.x + 25;
		this->laserOrig.y = this->m_Position.y - 30;
		this->laserDest.x = this->m_Position.x + laserRange;
		this->laserDest.y = this->m_Position.y - 6;
		this->visionLaser.updateLine(this->laserOrig, this->laserDest);
	}
}

/*
*	Updates the LaserPointer object for current frame
*/
void LaserPointer::update(sf::Time m_GameTimeTotal) {
	if (active) {
		if (m_GameTimeTotal.asMilliseconds() -
			lastToggleEvent.asMilliseconds() > 15000) {
			laserRange = 0;
			active = false;
			//std::cout << "\nLaser off!!";
			lastToggleEvent = m_GameTimeTotal;
		}
	}
	else {
		if (m_GameTimeTotal.asMilliseconds() -
			lastToggleEvent.asMilliseconds() > 5000) {
			laserRange = maxLaserRange;
			active = true;
			//std::cout << "\nLaser on!!";
			lastToggleEvent = m_GameTimeTotal;
		}
	}
}

/*
*	Return the ConvexShape that is the laser of the LaserPointer
*/
sf::ConvexShape LaserPointer::getLaser() {
	return visionLaser.getLine();
}

/*
*	Return Whether or not the laser is currently active
*/
bool LaserPointer::isActive() {
	return active;
}

/**
*	Return the name of this Class for comparison
*/
sf::String LaserPointer::getClassName() {
	return(sf::String("LaserPointer"));
}


