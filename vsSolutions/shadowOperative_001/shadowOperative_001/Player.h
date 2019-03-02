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

class Player : public PlayableCharacter {
public:
	// A constructor specific to Player
	Player();

	virtual void update(float elapsedTime, int** m_ArrayLevel);

	// The overriden input handler for Player
	virtual void PlayableCharacter::handleInput();

	int getDetectLevel();
	sf::Text getHudDetectLevel();

	bool isShooting();
	void playerShot(bool shot);

	void chargeGun(float dtAsSeconds);
	void chargeFromPickup(float charge,SoundManager& m_SM);
	float getChargeLevel();
	float getShotCost();
	float getMaxCharge();
	
	//aiming
	virtual void toggleTargeting(SoundManager& m_SM);
	virtual bool isTargeting();
	sf::Vector2f getTarget();
	
	//Conditions which decide targeting laser Origin
	void updateTargeting();
	sf::ConvexShape getlaser();

	sf::String getClassName();

	virtual void setShooting();

private:
	//Detection Level - Higher the value tyhe faster enemies detect the player
	int detectionLevel;
	//Default gun charge level
	float gunChargeLevel = 100.0f;
	//Modifies how fast the gun recharges
	const float gunChargeRate = 2.0f;
	//Maximum charge Level of the gun = gunChargeLevel default  
	const float maxGunChargeLevel = gunChargeLevel;
	//How much energy a shot uses
	float shotCost = 10.0f;
	//Text used to display detection state to the screen
	sf::Text hudText;

	//aiming
	bool targeting = false;	
};
#endif // !PLAYER_H