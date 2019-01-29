/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description
*/

#pragma once
#ifndef LASER_H
#define LASER_H

#include <SFML/Graphics.hpp>
class laser
{
private:
	//ConvexShape that constitutes the Laser object
	sf::ConvexShape laserLine;
public:
	void updateLine(sf::Vector2f playPos, sf::Vector2f mousePos);
	sf::ConvexShape getLine();
	laser();

private:
	sf::ConvexShape laserLine;
};

#endif	//	!LASER_H
