/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description	..
*
*	@notes	1.		Exchange m_rightPressed for direction::right
*/

#include "Player.h"
#include "TextureHolder.h"

Player::Player() {
	int	maxJumps = 2;
}
int Player::getDetectLevel()
{
	return detectionLevel;
}
void Player::update(float elapsedTime, int** m_ArrayLevel) {
	// Handle Actions
	if (this->m_Action == Action::IDLE) {

	}
	else if (this->m_Action == Action::WALKING) {

	}
	else if (this->m_Action == Action::FALLING) {
		this->m_Position.y += this->m_Gravity * elapsedTime;
	}
	else if (this->m_Action == Action::JUMPING) {
		// Update how long the jump has been going
		this->m_jumpDuration += elapsedTime;

		// Add the jump time to the timer
		this->m_Position.y -= this->m_Gravity * 2 * elapsedTime;

		// Character jump has gone on long enough
		if (this->m_jumpDuration >= this->maxJumpDuration) {
			this->m_Action = Action::FALLING;
		}
	}
	else if (this->m_Action == Action::CROUCHING) {

	}
	
	// Handle Direction
	if (m_Direction == Direction::IDLE) {
		// Look at the Nearest Enemy
		
		// Set Sprite to IDLE
		m_Sprite = sf::Sprite(TextureHolder::GetTexture(
			"graphics/idle__001.png"));
	}
	else if (this->m_Direction == Direction::RIGHT) {
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

	else if (this->m_Action == Action::FALLING) {
		// Set Player Sprite to Falling
		this->m_Sprite = sf::Sprite(TextureHolder::GetTexture(
			"graphics/Glide_000.png"));
	}

	// Update the rect for all body parts
	sf::FloatRect r = this->getPosition();
	
	// Feet
	this->m_Feet.left = m_Position.x;
	this->m_Feet.top = m_Position.y + (r.height * 0.9);
	this->m_Feet.width = r.width;
	this->m_Feet.height = r.height * 0.1;

	// Head
	this->m_Head.left = m_Position.x;
	this->m_Head.top = m_Position.y;
	this->m_Head.width = r.width;
	this->m_Head.height = r.height * 0.1;

	// Right
	this->m_Right.left = m_Position.x + (r.width * 0.9);
	this->m_Right.top = m_Position.y + (r.height * 0.1);
	this->m_Right.width = r.width * 0.1;
	this->m_Right.height = r.height * 0.8;

	// Left
	this->m_Left.left = m_Position.x;
	this->m_Left.top = m_Position.y + (r.height * 0.1);
	this->m_Left.width = r.width * 0.1;
	this->m_Left.height = r.height * 0.8;

	// Move the sprite into position
	this->m_Sprite.setPosition(this->m_Position);

	//charge weapon
	chargeGun(elapsedTime);
}

// A virtual function
void Player::handleInput() {
	//  Jumping
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		// Character not already jumping
		if (this->m_jumpCounter < this->maxJumps) {

			this->m_Action = Action::JUMPING;
			this->m_jumpCounter++;
		}
	}

	//  Moving Left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		//this->m_Action = Action::WALKING;
		this->m_Direction = Direction::LEFT;
	}
	//  Moving Right
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		//this->m_Action = Action::WALKING;
		this->m_Direction = Direction::RIGHT;
	}
	
	// If nothing is pressed
	/*if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A)
		&& !sf::Keyboard::isKeyPressed(sf::Keyboard::D)
		&& this->m_Action != Action::JUMPING
		&& this->m_Action != Action::FALLING) {*/
	else {
		//this->m_Action = Action::IDLE;
		this->m_Direction = Direction::IDLE;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		shooting = true;
	}
	else
	{
		shooting = false;
	}
	
}
bool Player::isShooting()
{
	return shooting;
}
void Player::playerShot(bool shot)
{
	gunChargeLevel -= shotCost;
	shooting = false;
}
void Player::chargeGun(float dtAsSeconds)
{
	if (!shooting)
	{
		if (gunChargeLevel + gunChargeRate * dtAsSeconds <= maxGunChargeLevel)
		{
			std::cout << "\n gunChargeLevel:" << gunChargeLevel << " += gunChargeRate * dtAsSeconds = "
				<< gunChargeLevel + gunChargeRate * dtAsSeconds;
			gunChargeLevel += gunChargeRate * dtAsSeconds;
		}
		else
		{
			gunChargeLevel = maxGunChargeLevel;
		}
	}
}
float Player::getChargeLevel()
{
	return gunChargeLevel;
}
float Player::getShotCost()
{
	return shotCost;
}
float Player::getMaxCharge()
{
	return maxGunChargeLevel;
}