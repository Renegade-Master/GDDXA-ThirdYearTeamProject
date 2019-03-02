/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description
*/

#include "SoundManager.h"

/**
*	Default Constructor
*/
SoundManager::SoundManager() noexcept {
	// Load the sound in to the buffers
	m_ButtonClickBuffer.loadFromFile("sound\\ButtonClick.wav");
	m_ChargeFromPickupBuffer.loadFromFile("sound\\weaponChargePickup.wav");
	m_EnemyCratedBuffer.loadFromFile("sound\\EnemyCrated.wav");
	m_EnemyDetectionLevel0Buffer.loadFromFile("sound\\EnemyAlertLevel_01.wav");
	m_EnemyDetectionLevel1Buffer.loadFromFile("sound\\EnemyAlertLevel_02.wav");
	m_EnemyDetectionLevel2Buffer.loadFromFile("sound\\EnemyAlertLevel_03.wav");
	m_EnemyDetectionLevel3Buffer.loadFromFile("sound\\EnemyAlertDetected.wav");
	m_EnemyHitBuffer.loadFromFile("sound\\EnemyHit.wav");
	m_EnemyUnconscoiusBuffer.loadFromFile("sound\\EnemyUnconscious.wav");
	m_JumpBuffer.loadFromFile("sound\\PlayerJump.wav");
	m_LaserPowerDownBuffer.loadFromFile("sound\\LaserPowerDown.wav");
	m_LaserPowerUpBuffer.loadFromFile("sound\\LaserPowerUp.wav");
	m_PlayerShootBuffer.loadFromFile("sound\\PlayerShoot_002.wav");
	m_ReachGoalBuffer.loadFromFile("sound\\LevelComplete.wav");

	// Associate the sounds with the buffers
	m_ButtonClickSound.setBuffer(m_ButtonClickBuffer);
	m_ChargeFromPickupSound.setBuffer(m_ChargeFromPickupBuffer);
	m_EnemyCratedSound.setBuffer(m_EnemyCratedBuffer);
	m_EnemyDetectionLevel0Sound.setBuffer(m_EnemyDetectionLevel0Buffer);
	m_EnemyDetectionLevel1Sound.setBuffer(m_EnemyDetectionLevel1Buffer);
	m_EnemyDetectionLevel2Sound.setBuffer(m_EnemyDetectionLevel2Buffer);
	m_EnemyDetectionLevel3Sound.setBuffer(m_EnemyDetectionLevel3Buffer);
	m_EnemyHitSound.setBuffer(m_EnemyHitBuffer);
	m_EnemyUnconsciousSound.setBuffer(m_EnemyUnconscoiusBuffer);
	m_JumpSound.setBuffer(m_JumpBuffer);
	m_LaserPowerDownSound.setBuffer(m_LaserPowerDownBuffer);
	m_LaserPowerUpSound.setBuffer(m_LaserPowerUpBuffer);
	m_PlayerShootSound.setBuffer(m_PlayerShootBuffer);
	m_ReachGoalSound.setBuffer(m_ReachGoalBuffer);

	//	Change the volume of certain effects
	m_ButtonClickSound			.setVolume(100.0f);
	m_ChargeFromPickupSound		.setVolume(100.0f);
	m_EnemyCratedSound			.setVolume(100.0f);
	m_EnemyDetectionLevel0Sound	.setVolume(100.0f);
	m_EnemyDetectionLevel1Sound	.setVolume(100.0f);
	m_EnemyDetectionLevel2Sound	.setVolume(100.0f);
	m_EnemyDetectionLevel3Sound	.setVolume(100.0f);
	m_EnemyHitSound				.setVolume(100.0f);
	m_EnemyUnconsciousSound		.setVolume(100.0f);
	m_JumpSound					.setVolume(100.0f);
	m_LaserPowerDownSound		.setVolume(100.0f);
	m_LaserPowerUpSound			.setVolume(100.0f);
	m_PlayerShootSound			.setVolume(100.0f);
	m_ReachGoalSound			.setVolume(100.0f);
}

/**
*	Play the Button Click Sound
*/
void SoundManager::playButtonClick() {
	m_ButtonClickSound.setRelativeToListener(true);
	m_ButtonClickSound.play();
}

/**
*	Play the Jump Sound
*/
void SoundManager::playJump() {
	m_JumpSound.setRelativeToListener(true);
	m_JumpSound.play();
}

/**
*	Play the Reach Goal Sound
*/
void SoundManager::playReachGoal() {
	m_ReachGoalSound.setRelativeToListener(true);
	m_ReachGoalSound.play();
}

/**
*	Play the Player Shooting Sound
*/
void SoundManager::playPlayerShoot() {
	m_PlayerShootSound.setRelativeToListener(true);
	m_PlayerShootSound.play();
}

/**
*	Play the Laser Powering Up Sound
*/
void SoundManager::playLaserPowerUp() {
	m_LaserPowerUpSound.setRelativeToListener(true);
	m_LaserPowerUpSound.play();
}

/**
*	Play the Laser Powering Down Sound
*/
void SoundManager::playLaserPowerDown() {
	m_LaserPowerDownSound.setRelativeToListener(true);
	m_LaserPowerDownSound.play();
}

/**
*	Play the EnemyHit  Sound
*/
void SoundManager::playEnemyHit() {
	m_EnemyHitSound.setRelativeToListener(true);
	m_EnemyHitSound.play();
}

/**
*	Play the Enemy Unconscious Sound
*/
void SoundManager::playEnemyUnconscious() {
	m_EnemyUnconsciousSound.setRelativeToListener(true);
	m_EnemyUnconsciousSound.play();
}

/**
*	Play the Enemy Crate Sound
*/
void SoundManager::playEnemyCrated() {
	m_EnemyCratedSound.setRelativeToListener(true);
	m_EnemyCratedSound.play();
}

/**
*	Play the Detection Sound
*/
void SoundManager::playEnemyDetectionLevel(int alertness) {
	//std::cout << "\nAlertness" << alertness;
	switch (alertness) {
	case 0:
		//std::cout << "\nCase 0\n";
		m_EnemyDetectionLevel0Sound.setRelativeToListener(true);
		m_EnemyDetectionLevel0Sound.play();
		break;
	case 1:
		//std::cout << "\nCase 1\n";
		m_EnemyDetectionLevel1Sound.setRelativeToListener(true);
		m_EnemyDetectionLevel1Sound.setLoop(true);
		m_EnemyDetectionLevel1Sound.play();
		break;
	case 2:
		//std::cout << "\nCase 2\n";
		m_EnemyDetectionLevel2Sound.setRelativeToListener(true);
		m_EnemyDetectionLevel2Sound.play();
		break;
	case 3:
		//std::cout << "\nCase 3\n";
		m_EnemyDetectionLevel3Sound.setRelativeToListener(true);
		m_EnemyDetectionLevel3Sound.play();
		break;
	default:
		//std::cout << "\nCase DEFAULT\n";
		m_EnemyDetectionLevel0Sound.setRelativeToListener(true);
		m_EnemyDetectionLevel0Sound.play();
		break;
	}
}

/**
*	Play the Charge From Pickup Sound
*/
void SoundManager::playChargeFromPickup() {
	m_ChargeFromPickupSound.setRelativeToListener(true);
	m_ChargeFromPickupSound.play();
}