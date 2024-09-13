#include <SFML/Graphics.hpp>
#include "particle.hpp"
#include "particle_system.hpp"
#include "utils.hpp"
#include <iostream>
#include <cmath>
#include <windows.h>

// Window constants
#define WIDTH 1920
#define HEIGHT 1080
#define FRAMERATE 60

// mass in solar masses
// distance in astronomical units
// speed in astronomical units per day

// Simulation constants
constexpr float SYSTEM_RADIUS = 6;
constexpr float MERCURY_RADIUS = 0.4;
constexpr float VENUS_RADIUS = 0.72;
constexpr float EARTH_RADIUS = 1;
constexpr float MOON_RADIUS = EARTH_RADIUS + 0.00257;
constexpr float MARS_RADIUS = 1.489;
constexpr float JUPITER_RADIUS = 5.2;
constexpr float SATURN_RADIUS = 9.5;
constexpr float URANUS_RADIUS = 19;
constexpr float NEPTUNE_RADIUS = 30;

constexpr float SUN_MASS = 1;

constexpr float MERCURY_MASS = 1.651 * pow(10, -7);
constexpr float VENUS_MASS = 2.44 * pow(10, -6);
constexpr float EARTH_MASS = 3 * pow(10, -6);
constexpr float MOON_MASS = 3.69 * pow(10, -8);
constexpr float MARS_MASS = 3.212 * pow(10, -7);
constexpr float JUPITER_MASS = 0.00095;
constexpr float SATURN_MASS = 0.000286;
constexpr float URANUS_MASS = 5 * pow(10, -5);
constexpr float NEPTUNE_MASS = 0.0000515;

constexpr float MERCURY_VELOCITY = 0.0271;
constexpr float VENUS_VELOCITY = 0.0202;
constexpr float EARTH_VELOCITY = 2 * PI / 365;
constexpr float MOON_VELOCITY = EARTH_VELOCITY + 0.000591;
constexpr float MARS_VELOCITY = 0.0139;
constexpr float JUPITER_VELOCITY = 0.0075;
constexpr float SATURN_VELOCITY = 0.0056;
constexpr float URANUS_VELOCITY = 0.0039;
constexpr float NEPTUNE_VELOCITY = 0.0031;

int main()
{

    HWND hWnd = GetConsoleWindow();
    ShowWindow( hWnd, SW_HIDE );
    
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Sim");

    Particle sun(sf::Vector2f(0, 0),sf::Vector2f(0, 0),sf::Vector2f(0, 0), 20, SUN_MASS, true, false, sf::Color(255, 255, 0));
    Particle mercury(sf::Vector2f(0, -MERCURY_RADIUS),sf::Vector2f(MERCURY_VELOCITY, 0),sf::Vector2f(0, 0), 3, MERCURY_MASS, false, true, sf::Color(173,168,165));
    Particle venus(sf::Vector2f(0, -VENUS_RADIUS),sf::Vector2f(VENUS_VELOCITY, 0),sf::Vector2f(0, 0), 4, VENUS_MASS, false, true, sf::Color(193,143,23));
    Particle earth(sf::Vector2f(0, -EARTH_RADIUS),sf::Vector2f(EARTH_VELOCITY, 0),sf::Vector2f(0, 0), 5, EARTH_MASS, false, true, sf::Color(101,148,188));
    Particle moon(sf::Vector2f(0, -MOON_RADIUS),sf::Vector2f(MOON_VELOCITY, 0),sf::Vector2f(0, 0), 1, MOON_MASS, false, true, sf::Color(100,100,100));
    Particle mars(sf::Vector2f(0, -MARS_RADIUS),sf::Vector2f(MARS_VELOCITY, 0),sf::Vector2f(0, 0), 4, MARS_MASS, false, true, sf::Color(193,68,14));
    Particle jupiter(sf::Vector2f(0, -JUPITER_RADIUS),sf::Vector2f(JUPITER_VELOCITY, 0),sf::Vector2f(0, 0), 7, JUPITER_MASS, false, true, sf::Color(201,144,57));
    Particle saturn(sf::Vector2f(0, -SATURN_RADIUS),sf::Vector2f(SATURN_VELOCITY, 0),sf::Vector2f(0, 0), 5, SATURN_MASS, false, true, sf::Color(227,152,17));
    Particle uranus(sf::Vector2f(0, -URANUS_RADIUS),sf::Vector2f(URANUS_VELOCITY, 0),sf::Vector2f(0, 0), 5, URANUS_MASS, false, true, sf::Color(209,231,231));
    Particle neptune(sf::Vector2f(0, -NEPTUNE_RADIUS),sf::Vector2f(NEPTUNE_VELOCITY, 0),sf::Vector2f(0, 0), 5, NEPTUNE_MASS, false, true, sf::Color(91,93,223));

    moon.scaleOrbit(&earth, 10);

    sf::Vector2f mouse_system_center(0,0);
    sf::Vector2f initial_mouse_system_center(0,0);
    sf::Vector2i initial_mouse_position(0,0);
    bool holding_mouse = false;

    ParticleSystem solver(SYSTEM_RADIUS, &sun.pos);

    solver.addParticle(&sun);
    solver.addParticle(&mercury);
    solver.addParticle(&venus);
    solver.addParticle(&earth);
    solver.addParticle(&moon);
    solver.addParticle(&mars);
    solver.addParticle(&jupiter);
    solver.addParticle(&saturn);
    solver.addParticle(&uranus);
    solver.addParticle(&neptune);

    window.setFramerateLimit(FRAMERATE);

    sf::Clock clock;

    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseWheelMoved)
            {

                if (event.mouseWheel.delta > 0 )
                {
                    solver.zoomIn(0.95);
                }
                else
                {

                    solver.zoomOut(1.05);

                }
            }
            else if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {

                    solver.setSystemCenterOnMouseParticle(window, sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

                }
            }

        }

        if( sf::Mouse::isButtonPressed( sf::Mouse::Button::Left ) )
        {

            sf::Vector2i mouse_position = sf::Mouse::getPosition( window );

            if (!holding_mouse) {
                initial_mouse_position = mouse_position;
                initial_mouse_system_center.x = solver.system_center->x;
                initial_mouse_system_center.y = solver.system_center->y;
                solver.setSystemCenter(&mouse_system_center);
            }
            holding_mouse = true;

            mouse_system_center.x = initial_mouse_system_center.x + fremap(initial_mouse_position.x - mouse_position.x,-WIDTH/2,WIDTH/2,-solver.system_radius,solver.system_radius);
            mouse_system_center.y = initial_mouse_system_center.y + fremap(initial_mouse_position.y - mouse_position.y,-HEIGHT/2,HEIGHT/2,-solver.system_radius,solver.system_radius);
        }
        else
        {

            holding_mouse = false;

        }
 

        window.clear();

        solver.update();
        solver.render(window);

        window.display();

    }

    return 0;
}