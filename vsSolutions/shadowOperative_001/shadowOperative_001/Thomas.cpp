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