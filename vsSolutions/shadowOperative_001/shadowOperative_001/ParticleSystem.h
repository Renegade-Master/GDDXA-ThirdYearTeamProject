/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[]
*					Rory Ryan	[]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description
*/

#pragma once
#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include <SFML/Graphics.hpp>
#include "Particle.h"

class ParticleSystem : public sf::Drawable {
private:
	std::vector<Particle> m_Particles;
	sf::VertexArray m_Vertices;
	float m_Duration;
	bool m_IsRunning = false;


public:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void init(int count);

	void emitParticles(sf::Vector2f position);

	void update(float elapsed);

	bool running();
};
#endif // !PARTICLESYSTEM_H


