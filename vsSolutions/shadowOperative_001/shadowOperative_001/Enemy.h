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

#include "PlayableCharacter.h"
#include "TextureHolder.h"
#include "visionCone.h"
#include"laser.h"



class Enemy : public PlayableCharacter {
private:
	sf::Vector2i m_SpawnPosition;
	bool patrolValid = false;
	// This is a pure virtual function
	virtual void handleInput();
	enum patrolDir { patrolLeft, patrolRight };
	patrolDir move = patrolLeft;
	friend patrolDir& operator++(patrolDir& mv, int incr);
	int sincePatrolAlter = 0;
	char direction;
	
protected:
	//Enemy Health
	float health = 100.0f;
	const float regenRate = 0.5f;
	const float maxHealth = 100.0f;
	bool concious = true;
	//Enemy Sight
	int sightAngle = 60;
	double detectionDistance = 500;
	const double maxDistance = detectionDistance;
	//This Characters cone of vision
	visionCone cone;
	laser visionLaser;
	float awarenessOfPlayer = 0.0f;
	//detection Event recorder used to slow execution of detection events to reasonable pace
	sf::Time lastDetectionEvent;
	//detection meter
	sf::RectangleShape detectMeter;
	sf::String getClassName();
	//what is the maximum distance of the laser
	double maxLaserRange;
	//what is the current maximum distance of the laser
	double laserRange = 500;

public:
	void update(float elapsedTIme,int** m_ArrayLevel/*, sf::Vector2f playPos*/);
	void spawn(sf::Vector2i startPosition, float gravity,sf::Time gameStart);
	void alterPatrol(bool patrol);
	sf::FloatRect getPosition();
	//bool detectPlayer(sf::Vector2f playPos);
	sf::ConvexShape getCone();
	void increaseAwarenessLevel(sf::Vector2f playPos,int detectionLevel,sf::Time gameTimeTotal);
	float getAwareness();
	double calcDistance(sf::Vector2f playPos,sf::Vector2f thisPos);
	float getlastdetectTime();
	sf::RectangleShape getDetectMeter();
	void reduceAwareness(sf::Time gameTimeTotal);
	
	//damage and healing
	void takeDamage(float shotPower);
	bool isConscious();
	void regen(float elapsedTime);
	void EnemyCrate();

	//Calculate Max field of vision
	double reCalculateMaxRange(char dir, int** m_ArrayLevel, double laserRange);


};

#endif // !ENEMY_H

