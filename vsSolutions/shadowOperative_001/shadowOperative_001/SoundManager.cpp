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
	this->m_ButtonClickBuffer.loadFromFile("sound\\ButtonClick.wav");
	this->m_ChargeFromPickupBuffer.loadFromFile("sound\\weaponChargePickup.wav");
	this->m_EnemyCratedBuffer.loadFromFile("sound\\EnemyCrated.wav");
	this->m_EnemyDetectionLevel0Buffer.loadFromFile("sound\\EnemyAlertLevel_01.wav");
	this->m_EnemyDetectionLevel1Buffer.loadFromFile("sound\\EnemyAlertLevel_02.wav");
	this->m_EnemyDetectionLevel2Buffer.loadFromFile("sound\\EnemyAlertLevel_03.wav");
	this->m_EnemyDetectionLevel3Buffer.loadFromFile("sound\\EnemyAlertDetected.wav");
	this->m_EnemyHitBuffer.loadFromFile("sound\\EnemyHit.wav");
	this->m_EnemyUnconscoiusBuffer.loadFromFile("sound\\EnemyUnconscious.wav");
	this->m_JumpBuffer.loadFromFile("sound\\PlayerJump.wav");
	this->m_LaserPowerDownBuffer.loadFromFile("sound\\LaserPowerDown.wav");
	this->m_LaserPowerUpBuffer.loadFromFile("sound\\LaserPowerUp.wav");
	this->m_PlayerShootBuffer.loadFromFile("sound\\PlayerShoot_002.wav");
	this->m_ReachGoalBuffer.loadFromFile("sound\\LevelComplete.wav");

	// Associate the sounds with the buffers
	this->m_ButtonClickSound.setBuffer(this->m_ButtonClickBuffer);
	this->m_ChargeFromPickupSound.setBuffer(this->m_ChargeFromPickupBuffer);
	this->m_EnemyCratedSound.setBuffer(this->m_EnemyCratedBuffer);
	this->m_EnemyDetectionLevel0Sound.setBuffer(this->m_EnemyDetectionLevel0Buffer);
	this->m_EnemyDetectionLevel1Sound.setBuffer(this->m_EnemyDetectionLevel1Buffer);
	this->m_EnemyDetectionLevel2Sound.setBuffer(this->m_EnemyDetectionLevel2Buffer);
	this->m_EnemyDetectionLevel3Sound.setBuffer(this->m_EnemyDetectionLevel3Buffer);
	this->m_EnemyHitSound.setBuffer(this->m_EnemyHitBuffer);
	this->m_EnemyUnconsciousSound.setBuffer(this->m_EnemyUnconscoiusBuffer);
	this->m_JumpSound.setBuffer(this->m_JumpBuffer);
	this->m_LaserPowerDownSound.setBuffer(this->m_LaserPowerDownBuffer);
	this->m_LaserPowerUpSound.setBuffer(this->m_LaserPowerUpBuffer);
	this->m_PlayerShootSound.setBuffer(this->m_PlayerShootBuffer);
	this->m_ReachGoalSound.setBuffer(this->m_ReachGoalBuffer);

	//	Change the volume of certain effects
	this->m_ButtonClickSound			.setVolume(this->m_UI_VOLUME);
	this->m_ChargeFromPickupSound		.setVolume(this->m_SFX_VOLUME);
	this->m_EnemyCratedSound			.setVolume(this->m_SFX_VOLUME);
	this->m_EnemyDetectionLevel0Sound	.setVolume(this->m_SFX_VOLUME);
	this->m_EnemyDetectionLevel1Sound	.setVolume(this->m_SFX_VOLUME);
	this->m_EnemyDetectionLevel2Sound	.setVolume(this->m_SFX_VOLUME);
	this->m_EnemyDetectionLevel3Sound	.setVolume(this->m_SFX_VOLUME);
	this->m_EnemyHitSound				.setVolume(this->m_SFX_VOLUME);
	this->m_EnemyUnconsciousSound		.setVolume(this->m_SFX_VOLUME);
	this->m_JumpSound					.setVolume(this->m_SFX_VOLUME);
	this->m_LaserPowerDownSound			.setVolume(this->m_SFX_VOLUME);
	this->m_LaserPowerUpSound			.setVolume(this->m_SFX_VOLUME);
	this->m_PlayerShootSound			.setVolume(this->m_SFX_VOLUME);
	this->m_ReachGoalSound				.setVolume(this->m_SFX_VOLUME);
}

/**
*	Play the Button Click Sound
*/
void SoundManager::playButtonClick() {
	this->m_ButtonClickSound.setVolume(this->m_UI_VOLUME);
	this->m_ButtonClickSound.play();
}

/**
*	Play the Charge From Pickup Sound
*/
void SoundManager::playChargeFromPickup() {
	this->m_ChargeFromPickupSound.setVolume(this->m_SFX_VOLUME);
	this->m_ChargeFromPickupSound.play();
}

/**
*	Play the Enemy Crate Sound
*/
void SoundManager::playEnemyCrated() {
	this->m_EnemyCratedSound.setVolume(this->m_SFX_VOLUME);
	this->m_EnemyCratedSound.play();
}

/**
*	Play the Jump Sound
*/
void SoundManager::playJump() {
	this->m_JumpSound.setVolume(this->m_SFX_VOLUME);
	this->m_JumpSound.play();
}

/**
*	Play the Reach Goal Sound
*/
void SoundManager::playReachGoal() {
	this->m_ReachGoalSound.setVolume(this->m_SFX_VOLUME);
	this->m_ReachGoalSound.play();
}

/**
*	Play the Player Shooting Sound
*/
void SoundManager::playPlayerShoot() {
	this->m_PlayerShootSound.setVolume(this->m_SFX_VOLUME);
	this->m_PlayerShootSound.play();
}

/**
*	Play the Laser Powering Up Sound
*/
void SoundManager::playLaserPowerUp() {
	this->m_LaserPowerUpSound.setVolume(this->m_SFX_VOLUME);
	this->m_LaserPowerUpSound.play();
}

/**
*	Play the Laser Powering Down Sound
*/
void SoundManager::playLaserPowerDown() {
	this->m_LaserPowerDownSound.setVolume(this->m_SFX_VOLUME);
	this->m_LaserPowerDownSound.play();
}

/**
*	Play the EnemyHit  Sound
*/
void SoundManager::playEnemyHit() {
	this->m_EnemyHitSound.setVolume(this->m_SFX_VOLUME);
	this->m_EnemyHitSound.play();
}

/**
*	Play the Enemy Unconscious Sound
*/
void SoundManager::playEnemyUnconscious() {
	this->m_EnemyUnconsciousSound.setVolume(this->m_SFX_VOLUME);
	this->m_EnemyUnconsciousSound.play();
}

/**
*	Play the Detection Sound
*/
void SoundManager::playEnemyDetectionLevel(int alertness) {
	//std::cout << "\nAlertness" << alertness;
	switch (alertness) {
	case 0:
		//std::cout << "\nCase 0\n";
		this->m_EnemyDetectionLevel0Sound.setVolume(this->m_SFX_VOLUME);
		this->m_EnemyDetectionLevel0Sound.play();
		break;
	case 1:
		//std::cout << "\nCase 1\n";
		this->m_EnemyDetectionLevel1Sound.setVolume(this->m_SFX_VOLUME);
		this->m_EnemyDetectionLevel1Sound.setLoop(true);
		this->m_EnemyDetectionLevel1Sound.play();
		break;
	case 2:
		//std::cout << "\nCase 2\n";
		this->m_EnemyDetectionLevel2Sound.setVolume(this->m_SFX_VOLUME);
		this->m_EnemyDetectionLevel2Sound.play();
		break;
	case 3:
		//std::cout << "\nCase 3\n";
		this->m_EnemyDetectionLevel3Sound.setVolume(this->m_SFX_VOLUME);
		this->m_EnemyDetectionLevel3Sound.play();
		break;
	default:
		//std::cout << "\nCase DEFAULT\n";
		this->m_EnemyDetectionLevel0Sound.setVolume(this->m_SFX_VOLUME);
		this->m_EnemyDetectionLevel0Sound.play();
		break;
	}
}