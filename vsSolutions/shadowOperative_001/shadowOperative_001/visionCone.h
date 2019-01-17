/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2019/01/16	YYYY/MM/DD
*	@description	
*	@notes	1.		Why are we using STRUCTS?
*/

#pragma once
#ifndef VISIONCONE_H
#define VISIONCONE_H

#include <algorithm>
#include <math.h>

#include <SFML/Graphics.hpp>

struct Line {
	sf::Vector2f p1;
	sf::Vector2f p2;
};
class visionCone {
private:
	sf::ConvexShape coneOfDetection;
public:
	void updateConePos(sf::Vector2f charPos,int charSightRange, int charSightAngle,bool faceRight);
	sf::ConvexShape getCone();
	visionCone();
};
#endif // !VISIONCONE_H

