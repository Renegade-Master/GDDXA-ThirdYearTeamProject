/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description
*/

#pragma once
#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML/Graphics.hpp>

class Particle {
private:
	sf::Vector2f m_Position;
	sf::Vector2f m_Velocity;

public:
	Particle(sf::Vector2f direction);

	void update(float dt);

	void setPosition(sf::Vector2f position);

	sf::Vector2f getPosition();
};
#endif // !PARTICLE_H
