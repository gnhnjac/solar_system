#pragma once
#include <vector>
#include "utils.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>

#define PI 3.1415926535

typedef struct {

        float orbit_mag;
        float angular_vel;
        float angle;
        float orbit_fluc_amp; // amplitude (strength) of orbit fluctuation
        float orbit_fluc_wlen; // speed (wavelength) of orbit fluctuation
        sf::CircleShape shape;

} Asteroid;

class AsteroidBelt
{

public:

        AsteroidBelt(int asteroid_count, int asteroid_seed = -1)
        {

                if (asteroid_seed == -1)
                {
                       srand (static_cast <unsigned> (time(0))); 
                }
                else
                {
                        srand(asteroid_seed);
                }

                for (int i = 0; i < asteroid_count; i++)
                {

                        float orbit_magnitude = frand(2.2, 3.2);
                        float asteroid_vel = frand(0.0098183232, 0.014438304);
                        float angular_vel = asteroid_vel / orbit_magnitude;
                        float angle = frand(0,2 * PI);
                        float orbit_fluc_amp = frand(0, 0.1);
                        float orbit_fluc_wlen = frand(0.5, 2);

                        m_asteroids.push_back(Asteroid {orbit_magnitude, angular_vel, angle, orbit_fluc_amp, orbit_fluc_wlen, sf::CircleShape(frand(0.5, 1))});

                }

        }

        void update();
        void render(sf::RenderWindow &, float, const sf::Vector2f);

private:

        std::vector<Asteroid> m_asteroids;

};