/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description	...
*
*	@notes	1.		Exchange m_rightPressed for direction::right
*/

#include "Player.h"
#include "TextureHolder.h"

Player::Player() {
	// Associate a texture with the sprite
	m_Sprite = sf::Sprite(TextureHolder::GetTexture(
		"graphics/idle__001.png"));

	/*m_SpriteRunningRight = sf::Sprite(TextureHolder::GetTexture(
		"graphics/RunRight__001.png"));

	m_SpriteRunningLeft = sf::Sprite(TextureHolder::GetTexture(
		"graphics/RunLeft__001.png"));

	m_SpriteFalling = sf::Sprite(TextureHolder::GetTexture(
		"graphics/Glide_000.png"));*/

	m_JumpDuration = 1;
}

void Player::update(float elapsedTime, int** m_ArrayLevel) {
	if (this->m_Direction == Direction::RIGHT) {
		this->m_Position.x += this->m_Speed * elapsedTime;

		//Changes the the sprite to runnning right
		this->m_Sprite = sf::Sprite(TextureHolder::GetTexture(
			"graphics/RunRight__001.png"));
	}
	else if (this->m_Direction == Direction::LEFT) {
		this->m_Position.x -= this->m_Speed * elapsedTime;

		//Changes the the sprite to running left
		this->m_Sprite = sf::Sprite(TextureHolder::GetTexture(
			"graphics/RunLeft__001.png"));
	}

	// Handle Jumping
	if (this->m_Action == Action::JUMPING) {
		// Update how long the jump has been going
		this->m_TimeThisJump += elapsedTime;

		// Has this jump gone on for too long?
		if (this->m_TimeThisJump < this->m_JumpDuration) {
			// Continue jumping
			this->m_Position.y -= this->m_Gravity * 2 * elapsedTime;
		}
		else {
			this->m_Action = Action::FALLING;
		}
	}

	// Apply gravity
	if (this->m_Action == Action::FALLING) {
		this->m_Position.y += this->m_Gravity * elapsedTime;
		this->m_SpriteFalling = sf::Sprite(TextureHolder::GetTexture(
			"graphics/Glide_000.png"));
	}

	// Update the rect for all body parts
	sf::FloatRect r = this->getPosition();


	// Feet
	this->m_Feet.left = r.left + 3;
	this->m_Feet.top = r.top + r.height - 1;
	this->m_Feet.width = r.width - 6;
	this->m_Feet.height = 1;

	// Head
	this->m_Head.left = r.left;
	this->m_Head.top = r.top + (r.height * .3);
	this->m_Head.width = r.width;
	this->m_Head.height = 1;

	// Right
	this->m_Right.left = r.left + r.width - 2;
	this->m_Right.top = r.top + r.height * .35;
	this->m_Right.width = 1;
	this->m_Right.height = r.height * .3;

	// Left
	this->m_Left.left = r.left;
	this->m_Left.top = r.top + r.height * .5;
	this->m_Left.width = 1;
	this->m_Left.height = r.height * .3;

	// Move the sprite into position
	this->m_Sprite.setPosition(this->m_Position);
	this->m_SpriteRunningRight.setPosition(this->m_Position);
	this->m_SpriteRunningLeft.setPosition(this->m_Position);
	this->m_SpriteFalling.setPosition(this->m_Position);

}

// A virtual function
void Player::handleInput() {
	//  Jumping
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		if (this->m_jumpCounter == 0
			&& this->m_Action != Action::JUMPING) {

			this->m_Action = Action::JUMPING;
			this->m_jumpCounter++;
		}
		else if (this->m_Action == Action::JUMPING
			&& this->m_jumpCounter < this->maxJumps
			&& this->m_TimeThisJump < this->m_JumpDuration) {

			this->m_jumpCounter++;
		}
		else if (this->m_Action == Action::JUMPING
			&& this->m_jumpCounter >= this->maxJumps
			&& this->m_TimeThisJump >= this->m_JumpDuration) {

			this->m_Action = Action::FALLING;
		}	
	}

	//  Moving Left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		this->m_Direction = Direction::LEFT;
	}

	//  Moving Right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		this->m_Direction = Direction::RIGHT;
	}

	// If nothing is pressed
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W)
		&& !sf::Keyboard::isKeyPressed(sf::Keyboard::A)
		&& !sf::Keyboard::isKeyPressed(sf::Keyboard::D)
		&& this->m_Action != Action::JUMPING
		&& this->m_Action != Action::FALLING) {
		
		this->m_Action = Action::IDLE;
		this->m_Direction = Direction::IDLE;
	}
}