/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description
*/

#include "Particle.h"

Particle::Particle(sf::Vector2f direction) {

	// Determine the direction
	//m_Velocity = direction;
	m_Velocity.x = direction.x;
	m_Velocity.y = direction.y;
}

void Particle::update(float dtAsSeconds) {
	// Move the particle
	m_Position += m_Velocity * dtAsSeconds;
}

void Particle::setPosition(sf::Vector2f position) {
	m_Position = position;

}

sf::Vector2f Particle::getPosition() {
	return m_Position;
}