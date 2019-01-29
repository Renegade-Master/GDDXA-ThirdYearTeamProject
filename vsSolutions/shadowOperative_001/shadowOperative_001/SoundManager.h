/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description
*/

#pragma once
#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <iostream>

#include <SFML/Audio.hpp>

class SoundManager {
private:
	// The buffers
	sf::SoundBuffer m_ButtonClickBuffer;
	sf::SoundBuffer m_JumpBuffer;
	sf::SoundBuffer m_ReachGoalBuffer;
	sf::SoundBuffer m_PlayerShootBuffer;
	sf::SoundBuffer m_LaserPowerUpBuffer;
	sf::SoundBuffer m_LaserPowerDownBuffer;
	sf::SoundBuffer m_EnemyHitBuffer;
	sf::SoundBuffer m_EnemyUnconscoiusBuffer;
	sf::SoundBuffer m_EnemyCratedBuffer;
	sf::SoundBuffer m_EnemyDetectionLevel0Buffer;
	sf::SoundBuffer m_EnemyDetectionLevel1Buffer;
	sf::SoundBuffer m_EnemyDetectionLevel2Buffer;
	sf::SoundBuffer m_EnemyDetectionLevel3Buffer;
	sf::SoundBuffer m_ChargeFromPickupBuffer;

	// The Sounds
	sf::Sound m_ButtonClickSound;
	sf::Sound m_JumpSound;
	sf::Sound m_ReachGoalSound;
	sf::Sound m_PlayerShootSound;
	sf::Sound m_LaserPowerUpSound;
	sf::Sound m_LaserPowerDownSound;
	sf::Sound m_EnemyHitSound;
	sf::Sound m_EnemyUnconsciousSound;
	sf::Sound m_EnemyCratedSound;
	sf::Sound m_EnemyDetectionLevel0Sound;
	sf::Sound m_EnemyDetectionLevel1Sound;
	sf::Sound m_EnemyDetectionLevel2Sound;
	sf::Sound m_EnemyDetectionLevel3Sound;
	sf::Sound m_ChargeFromPickupSound;

	// Which sound should we use next, fire 1, 2 or 3
	//int m_NextSound = 1;

public:
	SoundManager();

	void playButtonClick();
	void playJump();
	void playReachGoal();
	void playPlayerShoot();
	void playLaserPowerUp();
	void playLaserPowerDown();
	void playEnemyHit();
	void playEnemyUnconscious();
	void playEnemyCrated();
	void playEnemyDetectionLevel(int alertness);	
	void playChargeFromPickup();
};
#endif // !SOUNDMANAGER_H

