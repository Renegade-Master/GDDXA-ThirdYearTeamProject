#include "visionCone.h"

visionCone::visionCone()
{
	coneOfDetection.setPointCount(3);
	coneOfDetection.setFillColor(sf::Color::Red);
}
void visionCone::updateConePos(sf::Vector2f charPos, int charSightRange, int charSightAngle,bool faceRight)
{
	if (faceRight)
	{
		this->coneOfDetection.setPoint(0, charPos);
		this->coneOfDetection.setPoint(1, sf::Vector2f(charPos.x + charSightRange,charPos.y + charSightAngle));
		this->coneOfDetection.setPoint(2, sf::Vector2f(charPos.x + charSightRange, charPos.y - charSightAngle));
	}
	else
	{
		this->coneOfDetection.setPoint(0, charPos);
		this->coneOfDetection.setPoint(1, sf::Vector2f(charPos.x - charSightRange, charPos.y + charSightAngle));
		this->coneOfDetection.setPoint(2, sf::Vector2f(charPos.x - charSightRange, charPos.y - charSightAngle));
	}
}
sf::ConvexShape visionCone::getCone()
{
	return coneOfDetection;
}