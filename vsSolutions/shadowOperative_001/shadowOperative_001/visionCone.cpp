/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2019/01/16	YYYY/MM/DD
*	@description
*/

#include "visionCone.h"

visionCone::visionCone() {
	coneOfDetection.setPointCount(3);
	coneOfDetection.setFillColor(sf::Color::Color(255,0,0,100));
	double coneArea = ((coneOfDetection.getPoint(0).x*(coneOfDetection.getPoint(1).y - coneOfDetection.getPoint(2).y))
		+ (coneOfDetection.getPoint(1).x*(coneOfDetection.getPoint(2).y - coneOfDetection.getPoint(0).y))
		+ (coneOfDetection.getPoint(2).x*(coneOfDetection.getPoint(0).y - coneOfDetection.getPoint(1).y)));
}

void visionCone::updateConePos(sf::Vector2f charPos, int charSightRange, int charSightAngle,bool faceRight) {
	if (faceRight) {
		charPos.x += 50;
		this->coneOfDetection.setPoint(0, charPos);
		//X
		this->coneOfDetection.setPoint(
			1, 
			sf::Vector2f(
				charPos.x + charSightRange,
				charPos.y + charSightAngle)
		);
		//Y
		this->coneOfDetection.setPoint(
			2, sf::Vector2f(
				charPos.x + charSightRange,
				charPos.y - charSightAngle)
		);
	}
	else {
		this->coneOfDetection.setPoint(0, charPos);
		//X
		this->coneOfDetection.setPoint(
			1, 
			sf::Vector2f(
				charPos.x - charSightRange,
				charPos.y + charSightAngle)
		);
		//Y
		this->coneOfDetection.setPoint(
			2,
			sf::Vector2f(
				charPos.x - charSightRange,
				charPos.y - charSightAngle)
		);
	}
}
sf::ConvexShape visionCone::getCone() {
	return coneOfDetection;
}

void visionCone::updateCamConePos(sf::Vector2f charPos, int charSightRange,
	int charSightAngle, float cameraAngle, bool forward) {
	double angleRadians = (cameraAngle * (PIE / 180));
	std::cout <<"\nCamera angle "<< cameraAngle << "\nAngleRadians: " << angleRadians<<"\n\n\n";
	this->coneOfDetection.setPoint(0, charPos);
	this->coneOfDetection.setPoint(
		1,
		sf::Vector2f(
			//X
			charPos.x
			+ (-charSightRange
			* cos(angleRadians)),
			//Y
			(charPos.y
			+ (-charSightRange
			* sin(angleRadians))
			)+charSightAngle)
	);
	this->coneOfDetection.setPoint(
		2,
		sf::Vector2f(
			//X
			charPos.x
			+ (-charSightRange
			* cos(angleRadians)),
			//Y
			(charPos.y
			+ (-charSightRange
			* sin(angleRadians))
			)-charSightAngle)
	);
}