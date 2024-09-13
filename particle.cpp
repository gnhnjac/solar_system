#include "particle.hpp"
#include "utils.hpp"
#include <cmath>
#include <iostream>
#include <algorithm>

void Particle::render(sf::RenderWindow &win, float system_radius, const sf::Vector2f system_center)
{

	sf::Vector2f screen_pos = getScreenCoords(win, system_radius, system_center);

	if (screen_pos.x + m_radius < 0 || screen_pos.x - m_radius >= win.getSize().x || screen_pos.y + m_radius < 0 || screen_pos.y - m_radius >= win.getSize().y)
	{

		sf::Vector2f arrow_vector(screen_pos.x - win.getSize().x/2, screen_pos.y - win.getSize().y/2);

		float arrow_vector_mag = sqrt(arrow_vector.x * arrow_vector.x + arrow_vector.y * arrow_vector.y);

		sf::Vector2f unit_arrow = arrow_vector / arrow_vector_mag;

		sf::Vector2f unit_arrow_perpendicular_clockwise(unit_arrow.y, -unit_arrow.x);

		sf::Vector2f arrow_head(std::min(std::max(0, (int)screen_pos.x),(int)win.getSize().x-1),std::min(std::max(0, (int)screen_pos.y),(int)win.getSize().y-1));

		sf::Vector2f arrow_tail = arrow_head - unit_arrow * 25.f;
		arrow_head = arrow_head - unit_arrow - unit_arrow * 5.f;

		sf::Vertex line[] =
		{
		    sf::Vertex(arrow_tail),
		    sf::Vertex(arrow_head),
		    sf::Vertex(arrow_head),
		    sf::Vertex(arrow_head - unit_arrow * 5.f + unit_arrow_perpendicular_clockwise * 3.f),
		    sf::Vertex(arrow_head),
		    sf::Vertex(arrow_head - unit_arrow * 5.f - unit_arrow_perpendicular_clockwise * 3.f)
		};

		win.draw(line, 6, sf::Lines);

		float indicator_radius = m_radius / 2;

		sf::CircleShape indicator_circle(indicator_radius);

		indicator_circle.setFillColor(m_color);

		indicator_circle.setPosition(arrow_tail - sf::Vector2f(indicator_radius,indicator_radius) - unit_arrow * 2.f * indicator_radius);

		win.draw(indicator_circle);


	}

	if (m_scale_orbit)
	{

		sf::Vector2f orbit_vector = screen_pos - m_orbit_parent->getScreenCoords(win,system_radius,system_center);
		screen_pos -= orbit_vector;
		orbit_vector /= (float)sqrt(orbit_vector.x * orbit_vector.x + orbit_vector.y * orbit_vector.y);
		orbit_vector *= m_orbit_magnitude;
		screen_pos += orbit_vector;

	}

	// add position to trail

	if (m_show_trail)
	{

		win.draw(&m_trail[0], m_trail.size(), sf::LinesStrip);

		if (++m_trail_resolution_counter == m_trail_resolution)
		{

			for(auto &vertex : m_trail) 
			{
				vertex.color.a = std::max(0, vertex.color.a - 5);
			}

			if (m_trail.size() > 0 && m_trail.front().color.a == 0) m_trail.erase(m_trail.begin());

			m_trail_resolution_counter = 0;

			m_trail.push_back(sf::Vertex(sf::Vector2f(screen_pos.x, screen_pos.y), m_trail_color));

		}

	}

	m_shape.setPosition(sf::Vector2f(screen_pos.x-m_radius,screen_pos.y-m_radius));

	win.draw(m_shape);

}

void Particle::update()
{

	if (!m_fixed)
	{
		m_vel += m_acc;
		m_pos += m_vel;
	}
}

void Particle::resetForces()
{

	m_acc *= 0.f;

}

void Particle::applyForce(sf::Vector2f f)
{

	m_acc += f / m_mass;

}

void Particle::collide(Particle& p2)
{

	m_vel = ((m_mass - p2.mass) * m_vel + 2 * p2.mass * p2.vel) / (m_mass + p2.mass); 

}

void Particle::attract(Particle& p2)
{

	float dist_x = m_pos.x - p2.pos.x;
	float dist_y = m_pos.y - p2.pos.y;
	float dist = sqrt(dist_x * dist_x + dist_y * dist_y);

	float angle = atan2(dist_y, dist_x);

	float force = -1 * (G * m_mass * p2.mass) / pow(dist, 2);

	applyForce(sf::Vector2f(force * cos(angle), force * sin(angle)));
	

}

void Particle::scaleOrbit(const Particle *parent, float magnitude)
{

	m_scale_orbit = true;
	m_orbit_magnitude = magnitude;
	m_orbit_parent = parent;

}

void Particle::setRadius(float r)
{

	m_radius = r;
	m_shape.setRadius(r);

}

sf::Vector2f Particle::getScreenCoords(sf::RenderWindow &win, float system_radius, const sf::Vector2f system_center) const
{

	return sf::Vector2f(fremap(m_pos.x - system_center.x, -system_radius, system_radius, 0, win.getSize().x)
		               ,fremap(m_pos.y - system_center.y, -system_radius, system_radius, 0, win.getSize().y));

}