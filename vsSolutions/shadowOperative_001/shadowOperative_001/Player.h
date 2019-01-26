/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description	...
*/

#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "PlayableCharacter.h"
#include "laser.h"

class Player : public PlayableCharacter {
public:
	// A constructor specific to Player
	Player();		// Was Player::Player() but that wasn't working

	virtual void update(float elapsedTime, int** m_ArrayLevel);

	// The overriden input handler for Player
	virtual void PlayableCharacter::handleInput();

	int getDetectLevel();

	bool isShooting();
	void playerShot(bool shot);

	void chargeGun(float dtAsSeconds);
	void chargeFromPickup(float charge);
	float getChargeLevel();
	float getShotCost();
	float getMaxCharge();
	//aiming
	void toggleTargeting();
	bool isTargeting();
	//Conditions which decide targeting laser Origin
	void updateTargeting(sf::Vector2f mousePos);
	sf::ConvexShape getlaser();

	sf::String getClassName();
private:
	bool shooting;
	int detectionLevel;
	float gunChargeLevel = 100.0f;
	float gunChargeRate = 2.0f;
	float maxGunChargeLevel = 100.0f;
	float shotCost = 10.0f;

	//aiming
	bool targeting = false;
	laser targetingLaser;
};
#endif // !PLAYER_H