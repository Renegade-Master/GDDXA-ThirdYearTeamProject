/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description
*/

#include "Laser.h"

/**
*	Default Constructor
*/
laser::laser(){
	laserLine.setPointCount(4);
	laserLine.setFillColor(sf::Color::Color(255, 0, 0, 25));
	laserLine.setOutlineThickness(1);
	laserLine.setOutlineColor(sf::Color::Color(255,0,0,100));
}

/**
*	Updates the points of the Convex Shape the Laser is built of
*/
void laser::updateLine(sf::Vector2f playPos, sf::Vector2f mousePos){
	this->laserLine.setPoint(0, sf::Vector2f(playPos.x+0.001+25,playPos.y+0.001+25));
	this->laserLine.setPoint(1, sf::Vector2f(playPos.x + 25, playPos.y + 25));
	this->laserLine.setPoint(2, sf::Vector2f(mousePos.x + 0.001, mousePos.y + 0.001));
	this->laserLine.setPoint(3, mousePos);
}

/**
*	Return the ConvexShape of the Laser object
*/
sf::ConvexShape laser::getLine(){
	return laserLine;
}