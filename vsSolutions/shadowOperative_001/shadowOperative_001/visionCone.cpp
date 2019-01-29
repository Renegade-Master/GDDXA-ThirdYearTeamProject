/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2019/01/16	YYYY/MM/DD
*	@description
*/

#include "visionCone.h"

/**
*	Default Constructor for VisionCone
*/
visionCone::visionCone() {
	coneOfDetection.setPointCount(3);
	coneOfDetection.setFillColor(sf::Color::Color(255,0,0,100));
}

/**
*	Update the Cone Position using Parent Object varibables
*/
void visionCone::updateConePos(sf::Vector2f charPos, int charSightRange, int charSightAngle,bool faceRight) {
	if (faceRight) {
		charPos.x += TILE_SIZE;
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

/**
*	Return tyhe ConvexShape that is the cone of detection
*/
sf::ConvexShape visionCone::getCone() {
	return coneOfDetection;
}

/**
*	Update The cone of detection for the cameras
*/
void visionCone::updateCamConePos(sf::Vector2f charPos, int charSightRange,
	int charSightAngle, float cameraAngle, bool forward, char direction) {
	
	//Convert angle(Degrees) to angle (radians)
	float angleRadians = (cameraAngle * (PIE / 180));
	
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