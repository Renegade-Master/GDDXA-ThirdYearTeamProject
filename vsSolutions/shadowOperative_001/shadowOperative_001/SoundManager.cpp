/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description
*/

#include "SoundManager.h"

SoundManager::SoundManager() {
	// Load the sound in to the buffers
	m_ButtonClickBuffer.loadFromFile("sound/ButtonClick.wav");
	m_JumpBuffer.loadFromFile("sound/jump.wav");
	m_ReachGoalBuffer.loadFromFile("sound/reachgoal.wav");

	// Associate the sounds with the buffers
	m_ButtonClickSound.setBuffer(m_ButtonClickBuffer);
	m_JumpSound.setBuffer(m_JumpBuffer);
	m_ReachGoalSound.setBuffer(m_ReachGoalBuffer);

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