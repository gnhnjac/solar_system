#pragma once
#include <vector>
#include "particle.hpp"

class ParticleSystem
{

public:

	const float& system_radius = m_system_radius;
	const sf::Vector2f *&system_center = m_system_center;

	ParticleSystem(float system_radius, const sf::Vector2f *system_center, std::vector<Particle*> p_list={}) : m_system_radius{system_radius}, m_system_center{system_center}
	{

		m_particles.insert(m_particles.end(), p_list.begin(), p_list.end());

	}

	void addParticle(Particle*);
	void update();
	void render(sf::RenderWindow&);

	void zoomIn(float=0.99);
	void zoomOut(float=1.01);

	void setSystemCenter(const sf::Vector2f*);
	void setSystemCenterOnMouseParticle(sf::RenderWindow &,const sf::Vector2i&);

private:

	float m_system_radius;
	const sf::Vector2f *m_system_center;

	std::vector<Particle*> m_particles;

};