/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description
*/

#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include "Laser.h"
#include "PlayableCharacter.h"
#include "TextureHolder.h"
#include "VisionCone.h"

class Enemy : public PlayableCharacter {
public:
	void update(float elapsedTIe,int** m_ArrayLevel);
	void spawn(sf::Vector2i startPosition, float gravity,sf::Time gameStart);
	void alterPatrol(bool patrol);
	sf::FloatRect getPosition();
	sf::ConvexShape getCone();
	void increaseAwarenessLevel(sf::Vector2f playPos,int detectionLevel,sf::Time gameTimeTotal,
		SoundManager& m_SM);
	float getAwareness();
	double calcDistance(sf::Vector2f playPos,sf::Vector2f thisPos);
	float getlastdetectTime();
	sf::RectangleShape getDetectMeter();
	void reduceAwareness(sf::Time gameTimeTotal);
	
	//	Damage and healing
	void takeDamage(float shotPower);
	bool isConscious();
	void regen(float elapsedTime);

	//	Calculate Max field of vision
	double reCalculateMaxRange(char dir, int** m_ArrayLevel, double laserRange);
	void toggleTargeting(SoundManager& m_SM);
	virtual bool isTargeting();

private:
	sf::Vector2i m_SpawnPosition;
	bool patrolValid = false;

	//	Inherited from Superclass
	virtual void PlayableCharacter::handleInput();
	
	int sincePatrolAlter = 0;
	char direction;
	
protected:
	//	Enemy Health
	float health = 100.0f;
	const float regenRate = 0.5f;
	const float maxHealth = 100.0f;
	bool concious = true;
	
	//	Enemy Line-of-Sight
	int sightAngle = 60;
	double detectionDistance = 500;
	const double maxDistance = detectionDistance;
	
	//	This Character's cone of vision
	visionCone cone;
	laser visionLaser;
	double laserRange = 500;
	double maxLaserRange;
	float awarenessOfPlayer = 0.0f;
	
	//	Detection Event recorder used to slow execution of detection events to reasonable pace
	sf::Time lastDetectionEvent;
	
	//	Detection meter
	sf::RectangleShape detectMeter;

	//	Return the name of this Class for comparison
	sf::String getClassName();
};

#endif // !ENEMY_H

