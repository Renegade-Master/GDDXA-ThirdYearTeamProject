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
	int charSightAngle, float cameraAngle, bool forward, char direction) {
	//Convert angle(Degrees) to angle (radians)
	double angleRadians = (cameraAngle * (PIE / 180));
	//std::cout <<"\nCamera angle "<< cameraAngle << "\nAngleRadians: " << angleRadians<<"\n\n\n";

	//Calculate exact origin using camera direction
	//Calculate the bounds of the visionCone
	
	calculatedOrigin = charPos;
	if (direction == 'v') {
		calculatedOrigin.x += 30;
		this->coneOfDetection.setPoint(0, calculatedOrigin);
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
				) - charSightAngle)
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
				) + charSightAngle)
		);
	}
	else if(direction == 'z'){
		calculatedOrigin.y += 30;
		this->coneOfDetection.setPoint(0, calculatedOrigin);
		this->coneOfDetection.setPoint(
			1,
			sf::Vector2f(
				//X
				charPos.x
				+ (-charSightRange
				* cos(angleRadians)-charSightAngle),
				//Y
				(charPos.y
				+ (-charSightRange
				* sin(angleRadians))
				))
		);
		this->coneOfDetection.setPoint(
			2,
			sf::Vector2f(
				//X
				charPos.x
				+ (-charSightRange
				* cos(angleRadians)+charSightAngle),
				//Y
				(charPos.y
				+ (-charSightRange
				* sin(angleRadians))
				))
		);
	}
	else if (direction == 'x') {
		calculatedOrigin.x -= 30;
		this->coneOfDetection.setPoint(0, calculatedOrigin);
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
				) - charSightAngle)
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
				) + charSightAngle)
		);
	}
	else if (direction == 'c') {
		calculatedOrigin.y -= 30;
		this->coneOfDetection.setPoint(0, calculatedOrigin);
		this->coneOfDetection.setPoint(
			1,
			sf::Vector2f(
				//X
				charPos.x
				+ (-charSightRange
				* cos(angleRadians)-charSightAngle),
				//Y
				(charPos.y
				+ (-charSightRange
				* sin(angleRadians))
				))
		);
		this->coneOfDetection.setPoint(
			2,
			sf::Vector2f(
				//X
				charPos.x
				+ (-charSightRange
				* cos(angleRadians)+charSightAngle),
				//Y
				(charPos.y
				+ (-charSightRange
				* sin(angleRadians))
				))
		);
	}
}