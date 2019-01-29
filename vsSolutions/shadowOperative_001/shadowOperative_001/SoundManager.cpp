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
SoundManager::SoundManager() {
	// Load the sound in to the buffers
	m_ButtonClickBuffer.loadFromFile("sound\\ButtonClick.wav");
	m_JumpBuffer.loadFromFile("sound\\jump.wav");
	m_ReachGoalBuffer.loadFromFile("sound\\reachgoal.wav");
	m_PlayerShootBuffer.loadFromFile("sound\\PlayerShoot_002.wav");
	m_LaserPowerUpBuffer.loadFromFile("sound\\LaserPowerUp.wav");
	m_LaserPowerDownBuffer.loadFromFile("sound\\LaserPowerDown.wav");
	m_EnemyHitBuffer.loadFromFile("sound\\EnemyHit.wav");
	m_EnemyCratedBuffer.loadFromFile("sound\\EnemyCrated.wav");
	m_EnemyDetectionLevel0Buffer.loadFromFile("sound\\");
	m_EnemyDetectionLevel1Buffer.loadFromFile("sound\\");
	m_EnemyDetectionLevel2Buffer.loadFromFile("sound\\");
	m_EnemyDetectionLevel3Buffer.loadFromFile("sound\\");

	// Associate the sounds with the buffers
	m_ButtonClickSound.setBuffer(m_ButtonClickBuffer);
	m_JumpSound.setBuffer(m_JumpBuffer);
	m_ReachGoalSound.setBuffer(m_ReachGoalBuffer);
	m_PlayerShootSound.setBuffer(m_PlayerShootBuffer);
	m_LaserPowerUpSound.setBuffer(m_LaserPowerUpBuffer);
	m_LaserPowerDownSound.setBuffer(m_LaserPowerDownBuffer);
	m_EnemyHitSound.setBuffer(m_EnemyHitBuffer);
	m_EnemyUnconsciousSound.setBuffer(m_EnemyUnconscoiusBuffer);
	m_EnemyCratedSound.setBuffer(m_EnemyCratedBuffer);
	m_EnemyDetectionLevel0Sound.setBuffer(m_EnemyDetectionLevel0Buffer);
	m_EnemyDetectionLevel1Sound.setBuffer(m_EnemyDetectionLevel1Buffer);
	m_EnemyDetectionLevel2Sound.setBuffer(m_EnemyDetectionLevel2Buffer);
	m_EnemyDetectionLevel3Sound.setBuffer(m_EnemyDetectionLevel3Buffer);

	// When the player is 50 pixels away sound is full volume
	float minDistance = 150;
	// The sound reduces steadily as the player moves further away
	float attenuation = 15;

	// Set all the attenuation levels
	//m_Fire1Sound.setAttenuation(attenuation);

	// Set all the minimum distance levels
	//m_Fire1Sound.setMinDistance(minDistance);

	// Loop all the fire sounds
	// when they are played
	//m_Fire1Sound.setLoop(true);
}

/**
*
*/
void SoundManager::playFire(sf::Vector2f emitterLocation, sf::Vector2f listenerLocation) {
	//// Where is the listener? Player.
	//sf::Listener::setPosition(listenerLocation.x, listenerLocation.y, 0.0f);

	//switch (m_NextSound) {
	//case 1:
	//	// Locate/move the source of the sound
	//	m_Fire1Sound.setPosition(emitterLocation.x, emitterLocation.y, 0.0f);

	//	if (m_Fire1Sound.getStatus() == sf::Sound::Status::Stopped) {
	//		// Play the sound, if its not already
	//		//m_Fire1Sound.play();
	//	}
	//	break;

	//case 2:
	//	// Do the same as previous for the second sound
	//	m_Fire2Sound.setPosition(emitterLocation.x, emitterLocation.y, 0.0f);

	//	if (m_Fire2Sound.getStatus() == sf::Sound::Status::Stopped) {
	//		//m_Fire2Sound.play();
	//	}
	//	break;

	//case 3:
	//	// Do the same as previous for the third sound
	//	m_Fire3Sound.setPosition(emitterLocation.x, emitterLocation.y, 0.0f);

	//	if (m_Fire3Sound.getStatus() == sf::Sound::Status::Stopped) {
	//		//m_Fire3Sound.play();
	//	}
	//	break;
	//}

	//// Increment to the next fire sound
	//m_NextSound++;

	//// Go back to 1 when the third sound has been started
	//if (m_NextSound > 3) {
	//	m_NextSound = 1;
	//}
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
*	Play the ... Sound
*/
void SoundManager::playLaserPowerUp() {
	m_LaserPowerUpSound.setRelativeToListener(true);
	m_LaserPowerUpSound.play();
}

/**
*	Play the ... Sound
*/
void SoundManager::playLaserPowerDown() {
	m_LaserPowerDownSound.setRelativeToListener(true);
	m_LaserPowerDownSound.play();
}

/**
*	Play the ... Sound
*/
void SoundManager::playEnemyHit() {
	m_EnemyHitSound.setRelativeToListener(true);
	m_EnemyHitSound.play();
}

/**
*	Play the ... Sound
*/
void SoundManager::playEnemyUnconscious() {
	m_EnemyUnconsciousSound.setRelativeToListener(true);
	m_EnemyUnconsciousSound.play();
}

/**
*	Play the ... Sound
*/
void SoundManager::playEnemyCrated() {
	m_EnemyCratedSound.setRelativeToListener(true);
	m_EnemyCratedSound.play();
}

/**
*	Play the ... Sound
*/
void SoundManager::playEnemyDetectionLevel(int alertness) {
	switch (alertness) {
	case 0:
		m_EnemyDetectionLevel0Sound.setRelativeToListener(true);
		m_EnemyDetectionLevel0Sound.play();
		break;
	case 1:
		m_EnemyDetectionLevel1Sound.setRelativeToListener(true);
		m_EnemyDetectionLevel1Sound.play();
		break;
	case 2:
		m_EnemyDetectionLevel2Sound.setRelativeToListener(true);
		m_EnemyDetectionLevel2Sound.play();
		break;
	case 3:
		m_EnemyDetectionLevel3Sound.setRelativeToListener(true);
		m_EnemyDetectionLevel3Sound.play();
		break;
	}
}
