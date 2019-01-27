#include "LaserPointer.h"

/*
*	Default constructor for LaserPointer
*/
LaserPointer::LaserPointer(){
	m_Sprite = sf::Sprite(TextureHolder::GetTexture(
		"graphics/LaserPointer.png"));
}
/*
*	initialises the variables of the LaserPointer object
*/
void LaserPointer::spawn(sf::Vector2i startPosition, float gravity, sf::Time gameStart, char dir) {
	this->m_Position = sf::Vector2f(startPosition);
	this->m_Position.x = this->m_Position.x * 50;
	this->m_Position.y = this->m_Position.y * 50;

	this->m_Sprite.setOrigin(this->getCenter().x - this->getCenter().x + 50,
		this->getCenter().y - this->getCenter().y + 1);


	//Orient the Object to the appropriate position
	if (dir == 'a') {//UP
		this->m_Position.y += 75;
		m_Sprite.setPosition(this->m_Position);
		m_Sprite.setRotation(90.0f);
		this->laserOrig.x = this->m_Position.x - 30;
		this->laserOrig.y = this->m_Position.y - 70;
		this->laserDest.x = this->m_Position.x - 4;
		this->laserDest.y = this->m_Position.y -laserRange;
		securityLaser.updateLine(this->laserOrig,this->laserDest);
	}
	else if (dir == 'n') {//DOWN
		this->m_Position.y -= 25;
		m_Sprite.setPosition(this->m_Position);
		m_Sprite.setRotation(-90.0f);
		this->laserOrig.x = this->m_Position.x - 20;
		this->laserOrig.y = this->m_Position.y + 20;
		this->laserDest.x = this->m_Position.x + 4;
		this->laserDest.y = this->m_Position.y + laserRange;
		securityLaser.updateLine(this->laserOrig, this->laserDest);
	}
	else if (dir == 'm') {//LEFT
		this->m_Position.x += 75;
		m_Sprite.setPosition(this->m_Position);
		this->laserOrig.x = this->m_Position.x - 70;
		this->laserOrig.y = this->m_Position.y - 20;
		this->laserDest.x = this->m_Position.x - laserRange;
		this->laserDest.y = this->m_Position.y ;
		securityLaser.updateLine(this->laserOrig, this->laserDest);
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
		securityLaser.updateLine(this->laserOrig, this->laserDest);
	}
	
}
/*
*	Updates the LaserPointer object for current frame
*/
void LaserPointer::update() {
	//to be continued
}

sf::ConvexShape LaserPointer::getLaser() {
	return securityLaser.getLine();
}
