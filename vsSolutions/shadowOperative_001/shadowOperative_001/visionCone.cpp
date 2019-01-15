#include "visionCone.h"

visionCone::visionCone()
{
	coneOfDetection.setPointCount(3);
	coneOfDetection.setFillColor(sf::Color::Color(255,0,0,100));
	double coneArea = ((coneOfDetection.getPoint(0).x*(coneOfDetection.getPoint(1).y - coneOfDetection.getPoint(2).y))
		+ (coneOfDetection.getPoint(1).x*(coneOfDetection.getPoint(2).y - coneOfDetection.getPoint(0).y))
		+ (coneOfDetection.getPoint(2).x*(coneOfDetection.getPoint(0).y - coneOfDetection.getPoint(1).y)));
}
void visionCone::updateConePos(sf::Vector2f charPos, int charSightRange, int charSightAngle,bool faceRight)
{
	if (faceRight)
	{
		charPos.x += 50;
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
