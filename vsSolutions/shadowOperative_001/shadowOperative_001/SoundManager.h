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
public:
	SoundManager() noexcept;

	//	Volume Controls
	float m_SFX_VOLUME = 100.0f;
	float m_MUSIC_VOLUME = 100.0f;
	float m_UI_VOLUME = 100.0f;

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

private:
	// The buffers
	//Sound buffer for button clicks
	sf::SoundBuffer m_ButtonClickBuffer;
	//Sound buffer for jumping sound
	sf::SoundBuffer m_JumpBuffer;
	//Sound buffer for ReachGoal sound
	sf::SoundBuffer m_ReachGoalBuffer;
	//Sound buffer for shooting sound
	sf::SoundBuffer m_PlayerShootBuffer;
	//Sound Buffer for laser powering up buffer
	sf::SoundBuffer m_LaserPowerUpBuffer;
	//Sound buffer for laser powering Down buffer
	sf::SoundBuffer m_LaserPowerDownBuffer;
	//Sound buffer for Enemy hit by bullet
	sf::SoundBuffer m_EnemyHitBuffer;
	//Sound buffer for Enemy knocked unconcious
	sf::SoundBuffer m_EnemyUnconscoiusBuffer;
	//Sound buffer for Enemy having crate placed over their head
	sf::SoundBuffer m_EnemyCratedBuffer;
	//Sound buffer for Enemy Detection Level increase
	sf::SoundBuffer m_EnemyDetectionLevel0Buffer;
	//Sound buffer for Enemy Detection Level increase
	sf::SoundBuffer m_EnemyDetectionLevel1Buffer;
	//Sound buffer for Enemy Detection Level increase
	sf::SoundBuffer m_EnemyDetectionLevel2Buffer;
	//Sound buffer for Enemy Detection Level increase
	sf::SoundBuffer m_EnemyDetectionLevel3Buffer;
	//Sound buffer for charging gun from Pickup
	sf::SoundBuffer m_ChargeFromPickupBuffer;

	// The Sound for clicking Buttons
	sf::Sound m_ButtonClickSound;
	// The Sound for jumping
	sf::Sound m_JumpSound;
	// The Sound for Reaching the goal
	sf::Sound m_ReachGoalSound;
	// The Sound for shooting
	sf::Sound m_PlayerShootSound;
	// The Sound for powering up the laser(targeting beam)
	sf::Sound m_LaserPowerUpSound;
	// The Sound for powering down the laser(targeting beam0
	sf::Sound m_LaserPowerDownSound;
	// The Sound for Enemy hit by bullet sound(bullet hitting object)
	sf::Sound m_EnemyHitSound;
	// The Sound for enemy being unconcious
	sf::Sound m_EnemyUnconsciousSound;
	// The Sound for Enemy having crate placed over their head
	sf::Sound m_EnemyCratedSound;
	// The Sound for incresed enemy detection Level
	sf::Sound m_EnemyDetectionLevel0Sound;
	// The Sound for incresed enemy detection Level
	sf::Sound m_EnemyDetectionLevel1Sound;
	// The Sound for incresed enemy detection Level
	sf::Sound m_EnemyDetectionLevel2Sound;
	// The Sound for incresed enemy detection Level
	sf::Sound m_EnemyDetectionLevel3Sound;
	// The Sound for charging from a pickup
	sf::Sound m_ChargeFromPickupSound;
};
#endif // !SOUNDMANAGER_H

