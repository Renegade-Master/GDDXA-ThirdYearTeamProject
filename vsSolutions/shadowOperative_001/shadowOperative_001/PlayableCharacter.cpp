/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description	...
*/

#include "PlayableCharacter.h"

/**
*	Create a new PlayableCharacter at the specified position.
*/
void PlayableCharacter::spawn(sf::Vector2i startPosition, float gravity) {
	// Place the player at the starting point
	this->m_Position.x = startPosition.x;
	this->m_Position.y = startPosition.y;

	// Initialize the gravity
	this->m_Gravity = gravity;

	// Move the sprite in to position
	this->m_Sprite.setPosition(this->m_Position);
	this->m_animationFrame = 0;
	
	// Initialise Movement stats
	this->m_Speed = 500.0f;
	this->m_Action = Action::IDLE;
	this->m_Direction = Direction::IDLE;
	this->m_jumpCounter = 0;
	this->m_jumpDuration = 0.0f;
}

/**
*	Update this PlayerCharacter with the time and Level data.
*/
void PlayableCharacter::update(float elapsedTime,int** m_ArrayLevel) {
	// Overridden
}

/**
*	Return a FloatRect containing this PlayableCharacter.
*/
sf::FloatRect PlayableCharacter::getPosition() {
	return this->m_Sprite.getGlobalBounds();
}

/**
*	Return the Centre point of this PlayableCharacter.
*/
sf::Vector2f PlayableCharacter::getCenter() {
	return sf::Vector2f(
		this->m_Position.x + this->m_Sprite.getGlobalBounds().width / 2,
		this->m_Position.y + this->m_Sprite.getGlobalBounds().height / 2
	);
}

/**
*	Return various hitboxes.
*/
sf::FloatRect PlayableCharacter::getFeet() {
	return this->m_Feet;
}

sf::FloatRect PlayableCharacter::getHead() {
	return this->m_Head;
}

sf::FloatRect PlayableCharacter::getLeft() {
	return this->m_Left;
}

sf::FloatRect PlayableCharacter::getRight() {
	return this->m_Right;
}

/**
*	Return this Object's Sprite.
*/
sf::Sprite PlayableCharacter::getSprite() {
	return this->m_Sprite;
}

/**
*	Stop FALLING when colliding with an Object.
*/
void PlayableCharacter::stopFalling(float position) {
	this->m_Position.y = position - this->getPosition().height;
	this->m_Sprite.setPosition(this->m_Position);
	
	this->m_jumpCounter = 0;
	this->m_jumpDuration = 0.0f;
	this->m_Action = Action::IDLE;
	//this->m_Direction = Direction::IDLE;
}

/**
*	Stop moving RIGHT when colliding with an Object.
*/
void PlayableCharacter::stopRight(float position) {

	this->m_Position.x = position - this->m_Sprite.getGlobalBounds().width;
	this->m_Sprite.setPosition(this->m_Position);
	//this->m_Action = Action::IDLE;
	this->m_Direction = Direction::IDLE;
}

/**
*	Stop moving LEFT when colliding with an Object.
*/
void PlayableCharacter::stopLeft(float position) {
	this->m_Position.x = position + this->m_Sprite.getGlobalBounds().width;
	this->m_Sprite.setPosition(this->m_Position);
	//this->m_Action = Action::IDLE;
	this->m_Direction = Direction::IDLE;
}

/**
*	Stop a Jump early when colliding.
*/
void PlayableCharacter::stopJump() {
	this->m_Action = Action::FALLING;
}
