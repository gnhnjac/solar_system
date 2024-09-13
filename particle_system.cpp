#include "particle_system.hpp"

void ParticleSystem::addParticle(Particle* p)
{

	m_particles.push_back(p);

}

void ParticleSystem::update()
{

	for(auto * p1 : m_particles) 
	{

		p1->resetForces();

		for(auto * p2 : m_particles) 
		{

			if (p1 != p2)
			{

				p1->attract(*p2);

			}

		}

	}

	for(auto * p : m_particles) 
	{

		p->update();

	}

}

void ParticleSystem::render(sf::RenderWindow &win)
{

	for(auto * p : m_particles)
	{

		p->render(win, m_system_radius, *m_system_center);

	}

}

void ParticleSystem::zoomIn(float multiplier)
{

	if (multiplier >= 1) multiplier = 0.99;

	m_system_radius *= multiplier;

	for (auto * p : m_particles)
	{

		p->setRadius(p->radius * (1/multiplier));
		p->orbit_magnitude = p->orbit_magnitude * (1/multiplier);

	}

}

void ParticleSystem::zoomOut(float multiplier)
{

	if (multiplier <= 1) multiplier = 1.01;

	m_system_radius *= multiplier;

	for (auto * p : m_particles)
	{

		p->setRadius(p->radius / multiplier);
		p->orbit_magnitude = p->orbit_magnitude / multiplier;

	}

}

void ParticleSystem::setSystemCenterOnMouseParticle(sf::RenderWindow &win, const sf::Vector2i& coords)
{

	for (auto * p : m_particles)
	{

		sf::Vector2f p_pos = p->getScreenCoords(win, m_system_radius,*m_system_center);

		if (p_pos.x - p->radius < coords.x && p_pos.x + p->radius > coords.x && p_pos.y - p->radius < coords.y && p_pos.y + p->radius > coords.y)
		{

			m_system_center = &p->pos;
			return;

		}

	}

}

void ParticleSystem::setSystemCenter(const sf::Vector2f* center)
{

	m_system_center = center;

}