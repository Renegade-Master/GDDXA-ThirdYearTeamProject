/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description
*/

#include "PlayableCharacter.h"
#include<iostream>
void PlayableCharacter::spawn(sf::Vector2i startPosition, float gravity) {
	// Place the player at the starting point
	m_Position.x = startPosition.x;
	m_Position.y = startPosition.y;

	// Initialize the gravity
	m_Gravity = gravity;

	// Move the sprite in to position
	m_Sprite.setPosition(m_Position);

}

void PlayableCharacter::update(float elapsedTime,int** m_ArrayLevel) {
	// Overridden
}

sf::FloatRect PlayableCharacter::getPosition() {
	return m_Sprite.getGlobalBounds();
}

sf::Vector2f PlayableCharacter::getCenter() {
	return sf::Vector2f(
		m_Position.x + m_Sprite.getGlobalBounds().width / 2,
		m_Position.y + m_Sprite.getGlobalBounds().height / 2
	);
}

sf::FloatRect PlayableCharacter::getFeet() {
	return m_Feet;
}

sf::FloatRect PlayableCharacter::getHead() {
	return m_Head;
}

sf::FloatRect PlayableCharacter::getLeft() {
	return m_Left;
}

sf::FloatRect PlayableCharacter::getRight() {
	return m_Right;
}

sf::Sprite PlayableCharacter::getSprite() {
	switch (m_Direction) {
	case Direction::NOT:
		return m_Sprite;
		break;
	
	case Direction::RIGHT:
		return m_SpriteRunningRight;
		break;

	case Direction::LEFT:
		return m_SpriteRunningLeft;
		break;

	}
	switch (m_State) {

	case State::FALLING:
		return m_SpriteFalling;
		break;
	}
}

void PlayableCharacter::stopFalling(float position) {
	m_Position.y = position - getPosition().height;
	m_Sprite.setPosition(m_Position);
	//m_IsFalling = false;
	m_State = State::IDLE;
	playerjump = 0;
	
	//m_Direction = Direction::NOT;
}

void PlayableCharacter::stopRight(float position) {

	m_Position.x = position - m_Sprite.getGlobalBounds().width;
	m_Sprite.setPosition(m_Position);
	//m_State = State::IDLE;
	//m_Direction = Direction::NOT;
}

void PlayableCharacter::stopLeft(float position) {
	m_Position.x = position + m_Sprite.getGlobalBounds().width;
	m_Sprite.setPosition(m_Position);
	//m_State = State::IDLE;
	//m_Direction = Direction::NOT;
}

void PlayableCharacter::stopJump() {
	// Stop a jump early 
	//m_IsJumping = false;
	//m_IsFalling = true;
	  m_State = State::FALLING;
	  //m_JustJumped = false;
	//m_Direction = Direction::NOT;
}