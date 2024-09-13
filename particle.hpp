#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>

#define PI 3.1415926535
constexpr float G = 2.96 * pow(10, -4);

class Particle
{

public:

	const float& mass = m_mass;
	const float& radius = m_radius;
	float& orbit_magnitude = m_orbit_magnitude;

	const sf::Vector2f& pos = m_pos;
	const sf::Vector2f& vel = m_vel;

	Particle(sf::Vector2f init_pos,
			 sf::Vector2f init_vel,
			 sf::Vector2f init_acc,
			 float radius,
			 float mass,
			 bool is_fixed = false,
			 bool show_trail = false,
			 sf::Color color = sf::Color(255,255,255),
			 sf::Color trail_color = sf::Color(255,255,255)) 
			 : m_pos{init_pos}
			 , m_vel{init_vel}
			 , m_acc{init_acc}
			 , m_radius{radius}
			 , m_mass{mass}
			 , m_fixed{is_fixed}
			 , m_show_trail{show_trail}
			 , m_color{color}
			 , m_trail_color{trail_color}
			 , m_shape{radius}
	{

		m_shape.setFillColor(m_color);
		m_trail_resolution = (int)m_radius/2;
	}

	void update();
	void render(sf::RenderWindow&, float, const sf::Vector2f);
	void resetForces();
	void applyForce(sf::Vector2f);
	void attract(Particle&);
	void collide(Particle&);

	void setRadius(float);
	void scaleOrbit(const Particle *, float);
	sf::Vector2f getScreenCoords(sf::RenderWindow &, float, const sf::Vector2f) const;

private:

	sf::Vector2f m_pos;
	sf::Vector2f m_vel;
	sf::Vector2f m_acc;

	float m_radius;

	float m_mass;

	bool m_fixed;

	bool m_show_trail;
	unsigned int m_trail_resolution;
	unsigned int m_trail_resolution_counter = 0;
	std::vector<sf::Vertex> m_trail;
	sf::Color m_trail_color;

	bool m_scale_orbit = false;
	float m_orbit_magnitude = 0;
	const Particle *m_orbit_parent;

	sf::Color m_color;
	sf::CircleShape m_shape;

};