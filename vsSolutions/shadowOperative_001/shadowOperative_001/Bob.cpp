/**
*	@author			Ciaran Bent [K00221230]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description
*/

#include "Bob.h"
#include "TextureHolder.h"

Bob::Bob() {
	// Associate a texture with the sprite
	m_Sprite = sf::Sprite(TextureHolder::GetTexture(
		"graphics/bob.png"));

	m_JumpDuration = .25;
}

bool Bob::handleInput() {
	m_JustJumped = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {

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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		m_LeftPressed = true;

	}
	else {
		m_LeftPressed = false;
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {

		m_RightPressed = true;;

	}
	else {
		m_RightPressed = false;
	}

	return m_JustJumped;
}