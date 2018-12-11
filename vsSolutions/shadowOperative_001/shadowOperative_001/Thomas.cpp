/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description
*/

#include "TextureHolder.h"
#include "Thomas.h"

Thomas::Thomas() {
	// Associate a texture with the sprite
	m_Sprite = sf::Sprite(TextureHolder::GetTexture(
		"graphics/thomas.png"));

	m_JumpDuration = .45;
}

void Thomas::update(float elapsedTime) {
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
}

// A virtual function
bool Thomas::handleInput() {
	m_JustJumped = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {

		// Start a jump if not already jumping
		// but only if standing on a block (not falling)
		if (!m_IsJumping && !m_IsFalling) {
			m_IsJumping = true;
			m_TimeThisJump = 0;
			m_JustJumped = true;
		}
	}
	else {
		m_IsJumping = false;
		m_IsFalling = true;

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		m_LeftPressed = true;
	}
	else {
		m_LeftPressed = false;
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		m_RightPressed = true;
	}
	else {
		m_RightPressed = false;
	}

	return m_JustJumped;
}