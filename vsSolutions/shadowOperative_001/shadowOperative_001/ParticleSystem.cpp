/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description
*/

#include <SFML/Graphics.hpp>
#include "ParticleSystem.h"

void ParticleSystem::init(int numParticles) {
	m_Vertices.setPrimitiveType(sf::Points);
	m_Vertices.resize(numParticles);

	// Create the particles

	for (int i = 0; i < numParticles; i++) {
		srand(time(0) + i);
		float angle = (rand() % 360) * 3.14f / 180.f;
		float speed = (rand() % 600) + 600.f;

		sf::Vector2f direction;

		direction = sf::Vector2f(cos(angle) * speed,
			sin(angle) * speed);

		m_Particles.push_back(Particle(direction));

	}

}

void ParticleSystem::update(float dt) {
	m_Duration -= dt;
	std::vector<Particle>::iterator i;
	int currentVertex = 0;

	for (i = m_Particles.begin(); i != m_Particles.end(); i++) {
		// Move the particle
		(*i).update(dt);

		// Update the vertex array
		m_Vertices[currentVertex].position = (*i).getPosition();

		// Move to the next vertex
		currentVertex++;
	}

	if (m_Duration < 0) {
		m_IsRunning = false;
	}

}

void ParticleSystem::emitParticles(sf::Vector2f startPosition) {
	m_IsRunning = true;
	m_Duration = 2;

	std::vector<Particle>::iterator i;
	int currentVertex = 0;

	for (i = m_Particles.begin(); i != m_Particles.end(); i++) {
		m_Vertices[currentVertex].color = sf::Color::Yellow;
		(*i).setPosition(startPosition);

		currentVertex++;
	}

}

void ParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	target.draw(m_Vertices, states);
}

bool ParticleSystem::running() {
	return m_IsRunning;
}