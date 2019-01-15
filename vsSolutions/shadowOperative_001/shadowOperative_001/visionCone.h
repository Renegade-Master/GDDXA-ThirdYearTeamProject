#pragma once
#ifndef VISIONCONE_H
#define VISIONCONE_H
#include <SFML/Graphics.hpp>
class visionCone
{
private:
	sf::FloatRect coneOfDetection;
public:
	void updateConePos(sf::Vector2f charPos,int charSightRange, int charSightAngle,bool faceRight);
	sf::FloatRect getCone();
};
#endif // !VISIONCONE_H

