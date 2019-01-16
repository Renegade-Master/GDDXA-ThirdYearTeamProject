/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description
*/

#include <iostream>
#include "TextureHolder.h"
#include "Player.h"

Player::Player() {
	// Associate a texture with the sprite
	m_Sprite = sf::Sprite(TextureHolder::GetTexture(
		"graphics/idle__001.png"));

	m_SpriteRunningRight = sf::Sprite(TextureHolder::GetTexture(
		"graphics/RunRight__001.png"));

	m_SpriteRunningLeft = sf::Sprite(TextureHolder::GetTexture(
		"graphics/RunLeft__001.png"));

	m_SpriteFalling = sf::Sprite(TextureHolder::GetTexture(
		"graphics/Glide_000.png"));

	m_JumpDuration = 2;
	detectionLevel = 2;
}
int Player::getDetectLevel()
{
	return detectionLevel;
}
void Player::update(float elapsedTime, int** m_ArrayLevel) {
	if (m_RightPressed) {
		m_Position.x += m_Speed * elapsedTime;
	}

	if (m_LeftPressed) {
		m_Position.x -= m_Speed * elapsedTime;
	}


	// Handle Jumping
	if (m_IsJumping) {
		// Update how long the jump has been going
		m_TimeThisJump += elapsedTime;

		// Is the jump going upwards
		if (m_TimeThisJump < m_JumpDuration) {
			// Move up at twice gravity
			m_Position.y -= m_Gravity * 2 * elapsedTime;
			//CharacterAnimation = State::FALLING;
		}
		else {
			m_IsJumping = false;
			m_IsFalling = true;	
		}

	}

	// Apply gravity
	if (m_IsFalling) {
		m_Position.y += m_Gravity * elapsedTime;
	}

	// Update the rect for all body parts
	sf::FloatRect r = getPosition();


	// Feet
	m_Feet.left = r.left + 3;
	m_Feet.top = r.top + r.height - 1;
	m_Feet.width = r.width - 6;
	m_Feet.height = 1;

	// Head
	m_Head.left = r.left;
	m_Head.top = r.top + (r.height * .3);
	m_Head.width = r.width;
	m_Head.height = 1;

	// Right
	m_Right.left = r.left + r.width - 2;
	m_Right.top = r.top + r.height * .35;
	m_Right.width = 1;
	m_Right.height = r.height * .3;

	// Left
	m_Left.left = r.left;
	m_Left.top = r.top + r.height * .5;
	m_Left.width = 1;
	m_Left.height = r.height * .3;

	// Move the sprite into position
	m_Sprite.setPosition(m_Position);
	m_SpriteRunningRight.setPosition(m_Position);
	m_SpriteRunningLeft.setPosition(m_Position);
	m_SpriteFalling.setPosition(m_Position);

}

// A virtual function
bool Player::handleInput() {
	m_JustJumped = false;
	CharacterAnimation = State::IDLE;

	switch (sf::Joystick::isConnected(-1)) { // Controller support DISABLED
		case true:
			//  Jumping
			if (sf::Joystick::isButtonPressed(0, 0)) {
				//std::cout << "Trying to jump (GamePad)" << std::endl;

				// Start a jump if not already jumping
				// but only if standing on a block (not falling)
				if (!m_IsJumping && !m_IsFalling) {
					m_IsJumping = true;
					m_TimeThisJump = 0;
					m_JustJumped = true;
					CharacterAnimation = State::FALLING;
				}
			}
			else {
				m_IsJumping = false;
				m_IsFalling = true;
				CharacterAnimation = State::FALLING;
			}

			//  Moving Left
			if (sf::Joystick::getAxisPosition(0, sf::Joystick::X) < -7.5) {
				m_LeftPressed = true;
				//Changes the the sprite to runnning right
				CharacterAnimation = State::RUNNINGLEFT;
			}
			else {
				m_LeftPressed = false;
				//Changes the the sprite to idle position
				//State CharacterAnimation = State::IDLE;
			}

			//  Moving Right
			if (sf::Joystick::getAxisPosition(0, sf::Joystick::X) > 7.5) {
				m_RightPressed = true;
				//Changes the the sprite to runnning right
			    CharacterAnimation = State::RUNNINGRIGHT;
			}
			else {
				m_RightPressed = false;
				//Changes the the sprite to idle position
				//State CharacterAnimation = State::IDLE;
			}
			break;
		case false:
			//  Jumping
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {

				// Start a jump if not already jumping
				// but only if standing on a block (not falling)
				if (!m_IsJumping && !m_IsFalling) {
					m_IsJumping = true;
					m_TimeThisJump = 0;
					m_JustJumped = true;
					CharacterAnimation = State::FALLING;
				}
			}
			else {
				m_IsJumping = false;
				m_IsFalling = true;
				CharacterAnimation = State::FALLING;
			}

			//  Moving Left
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				m_LeftPressed = true;
				//Changes the the sprite to running left
				CharacterAnimation = State::RUNNINGLEFT;
			}
			else {
				m_LeftPressed = false;
				//Changes the the sprite to idle position
				//CharacterAnimation = State::IDLE;
			}

			//  Moving Right
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				m_RightPressed = true;
				//Changes the the sprite to running right
				CharacterAnimation = State::RUNNINGRIGHT;
			}
			else {
				m_RightPressed = false;
				//Changes the the sprite to idle position
				//CharacterAnimation = State::IDLE;
			}
			break;
	}	
	return m_JustJumped;
}