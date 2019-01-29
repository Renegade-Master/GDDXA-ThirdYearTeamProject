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
#include <iostream>
#include <cmath>
#include <math.h>

#include <SFML/Graphics.hpp>

#include "Constants.h"

class visionCone {
private:
	sf::ConvexShape coneOfDetection;
	sf::Vector2f calculatedOrigin;
public:
	void updateConePos(sf::Vector2f charPos,int charSightRange, int charSightAngle,bool faceRight);
	void updateCamConePos(sf::Vector2f charPos, int charSightRange, int charSightAngle,
		float cameraAngle, bool forward, char direction);
	sf::ConvexShape getCone();
	visionCone();
};
#endif // !VISIONCONE_H

