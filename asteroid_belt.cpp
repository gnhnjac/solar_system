#include "asteroid_belt.hpp"

sf::Vector2f getScreenCoords(float x, float y, sf::RenderWindow &win, float system_radius, const sf::Vector2f system_center)
{

	return sf::Vector2f(fremap(x - system_center.x, -system_radius, system_radius, 0, win.getSize().x)
		               ,fremap(y - system_center.y, -system_radius, system_radius, 0, win.getSize().y));

}

void AsteroidBelt::update()
{

	for (Asteroid &a : m_asteroids)
	{

		a.orbit_mag -= a.orbit_fluc_amp * sin(a.angle * a.orbit_fluc_wlen);

		a.angle += a.angular_vel;

		a.orbit_mag += a.orbit_fluc_amp * sin(a.angle * a.orbit_fluc_wlen);

	}

}

void AsteroidBelt::render(sf::RenderWindow &win, float system_radius, const sf::Vector2f system_center)
{

	for (Asteroid a : m_asteroids)
	{

		float asteroid_x = a.orbit_mag * cos(a.angle);
		float asteroid_y = a.orbit_mag * sin(a.angle);

		sf::Vector2f screen_coords = getScreenCoords(asteroid_x, asteroid_y, win, system_radius, system_center);

		a.shape.setFillColor(sf::Color(150,150,150));

		a.shape.setPosition(screen_coords);

		win.draw(a.shape);

	}

}