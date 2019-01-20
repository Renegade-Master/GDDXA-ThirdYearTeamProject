#pragma once
#ifndef LASER_H
#define LASER_H
#include <SFML/Graphics.hpp>
class laser
{
private:
	sf::ConvexShape laserLine;
	
public:
	void updateLine(sf::Vector2f playPos, sf::Vector2f mousePos);
	sf::ConvexShape getLine();
	laser();
};
#endif
