#include "laser.h"

laser::laser(){
	laserLine.setPointCount(4);
	laserLine.setFillColor(sf::Color::Color(255, 0, 0, 25));
	laserLine.setOutlineThickness(1);
	laserLine.setOutlineColor(sf::Color::Color(255,0,0,100));
}
void laser::updateLine(sf::Vector2f playPos, sf::Vector2f mousePos){
	this->laserLine.setPoint(0, sf::Vector2f(playPos.x+0.001+25,playPos.y+0.001+25));
	this->laserLine.setPoint(1, sf::Vector2f(playPos.x + 25, playPos.y + 25));
	this->laserLine.setPoint(2, sf::Vector2f(mousePos.x + 0.001, mousePos.y + 0.001));
	this->laserLine.setPoint(3, mousePos);
}
sf::ConvexShape laser::getLine(){
	return laserLine;
}